#include "llvm/Transforms/CFMSE/CFMSE.h"
#include "CFMSEUtils.h"
#include "SymbolicVariableAnalysis.h"
#include "json.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TableGen/Record.h"
#include "llvm/Transforms/CFMSE/BBReplication.h"
#include "llvm/Transforms/CFMelder/CFMelder.h"
#include "llvm/Transforms/CFMelder/DebugInfoMerger.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <fstream>
#include <string>

// #define CFMSE_CFG_DEBUG

using namespace llvm;
using nlohmann::json;

static cl::opt<bool>
    RunCFMSEAnalysisOnly("cfmse-analysis-only", cl::init(false), cl::Hidden,
                         cl::desc("Run symbolic variable analysis only"));

static cl::opt<bool>
    CFMSEPrintSV("cfmse-print-sv", cl::init(false), cl::Hidden,
                 cl::desc("Print symbolic varibale analyis results"));

static cl::opt<std::string> CFMSEPrintSVFunc(
    "cfmse-print-sv-for-func", cl::init(""), cl::Hidden,
    cl::desc("Print symbolic varibale analyis for this function"));

static cl::opt<bool>
    CFMSEDiamondOnly("cfmse-diamond-only", cl::init(false), cl::Hidden,
                     cl::desc("Merge diamond shaped control flow only"));

static cl::opt<bool> ForceCFMSE(
    "force-cfmse", cl::init(false), cl::Hidden,
    cl::desc("Force CFMSE on all branches (non-symbolic, non-loop)"));

// define a statistic to count the number of times the pass is run
#define DEBUG_TYPE "cfmse"
STATISTIC(NumCFMSEMerges, "Counts number of times CFMSE pass is run");
STATISTIC(NumIfThenMerges, "Counts number of if-then merges");
STATISTIC(NumIfThenElseMerges, "Counts number of if-then-else merges");
STATISTIC(NumSelectsAdded, "Counts number of select instructions added");

namespace {
class CFMSELegacyPass : public ModulePass {
public:
  static char ID;
  CFMSELegacyPass() : ModulePass(ID) {
    initializeCFMSELegacyPassPass(*PassRegistry::getPassRegistry());
  }

  bool runOnModule(Module &M) override;

  void getAnalysisUsage(AnalysisUsage &AU) const override;
};
} // namespace

#ifdef CFMSE_CFG_DEBUG
static int Counter = 0;
#endif

static void
runAnalysisOnly(Module &M, function_ref<AAResults &(Function *F)> GetAAResult) {
  INFO("runAnalysisOnly is not implemented!\n");
  return;
}

static bool containsDontTouchLocs(const BasicBlock *BB1, const BasicBlock *BB2,
                                  CFMSEOptions &Options) {
  SmallVector<const Instruction *> Is;

  for (auto &I : *BB1) {
    Is.push_back(&I);
  }
  for (auto &I : *BB2) {
    Is.push_back(&I);
  }

  for (auto &I : Is) {
    DebugLoc DL = I->getDebugLoc();
    if (DL) {
      std::string Loc =
          DL->getFilename().str() + "::" + std::to_string(DL->getLine());
      if (Options.isDontTouchLoc(Loc)) {
        return true;
      }
    }
  }
  return false;
}

static bool containsSymbolicAddresses(const BasicBlock *BB1,
                                      const BasicBlock *BB2,
                                      ModuleSymbolicVariableAnalysis &MSV) {
  SmallVector<const Instruction *> Is;

  for (auto &I : *BB1) {
    Is.push_back(&I);
  }
  for (auto &I : *BB2) {
    Is.push_back(&I);
  }

  auto DoesGEPGiveSymbolicAddress = [&](const GetElementPtrInst *GEP) {
    // iterate over all index operands, if any of the index operands is symbolic
    // then the GEP computes a symbolic address
    for (auto &Op : GEP->indices()) {
      if (MSV.isSymbolic(*Op)) {
        return true;
      }
    }
    return false;
  };

  for (auto &I : Is) {
    if (const LoadInst *LI = dyn_cast<LoadInst>(I)) {
      // get the GEP
      if (const GetElementPtrInst *GEP =
              dyn_cast<GetElementPtrInst>(LI->getPointerOperand())) {
        if (DoesGEPGiveSymbolicAddress(GEP)) {
          return true;
        }
      }
    }
    if (const StoreInst *SI = dyn_cast<StoreInst>(I)) {
      if (const GetElementPtrInst *GEP =
              dyn_cast<GetElementPtrInst>(SI->getPointerOperand())) {
        if (DoesGEPGiveSymbolicAddress(GEP)) {
          return true;
        }
      }
    }
  }
  return false;
}

// function to count number of select instructions in a function
static int countSelects(const Function &F) {
  int NumSelects = 0;
  for (const BasicBlock &BB : F) {
    for (const Instruction &I : BB) {
      if (isa<SelectInst>(I)) {
        NumSelects++;
      }
    }
  }
  return NumSelects;
}

static int countTotalInstructions(const Function &F) {
  int NumInstructions = 0;
  for (const BasicBlock &BB : F) {
    NumInstructions += BB.size();
  }
  return NumInstructions;
}

static int countCondBranches(const Function &F) {
  int NumBranches = 0;

  for (const BasicBlock &BB : F) {
    for (const Instruction &I : BB) {
      if (const BranchInst *BI = dyn_cast<BranchInst>(&I)) {
        if (BI->isConditional()) {
          NumBranches++;
        }
      }
    }
  }
  return NumBranches;
}

static int countUnCondBranches(const Function &F) {
  int NumBranches = 0;

  for (const BasicBlock &BB : F) {
    for (const Instruction &I : BB) {
      if (const BranchInst *BI = dyn_cast<BranchInst>(&I)) {
        if (!BI->isConditional()) {
          NumBranches++;
        }
      }
    }
  }
  return NumBranches;
}
// this function tries to remove redundant unconditional branches
static void removeRedundantJumps(SmallVector<BasicBlock *> &ToProcess) {
#ifdef CFMSE_CFG_DEBUG
  // Function *F = ToProcess[0]->getParent();
  // writeCFGToDotFile(*F, "before_red_jumps" + std::to_string(Counter++));
#endif

  for (BasicBlock *BB : ToProcess) {
    BasicBlock *SingleSucc = BB->getSingleSuccessor();
    if (!SingleSucc)
      continue;

    bool OkToRemove = true;
    for (auto *Pred : predecessors(BB)) {
      if (Pred == SingleSucc) {
        OkToRemove = false;
        break;
      }
    }

    if (OkToRemove) {
      DEBUG("Trying to remove redundant jump from " + BB->getNameOrAsOperand() +
            " to " + SingleSucc->getNameOrAsOperand() + "..\n");
      if (MergeBlockIntoPredecessor(SingleSucc)) {
        DEBUG("Removed redundant jump!\n");
      }
    }
  }
}

static bool runCFMSEOnFunction(Function &F, FunctionAnalysisManager &FAM,
                               PreservedAnalyses &PA, CFMSEOptions &Options,
                               ModuleSymbolicVariableAnalysis &MSV) {
  DEBUG("Processing function : " + F.getName() + "\n");

#ifdef CFMSE_CFG_DEBUG
  // if (F.getName().contains("to_upper"))
  //   MSV.printForFunction(errs(), F.getName().str());
  if (F.getName().contains("num2str"))
    writeCFGToDotFile(F, "before_cfmse" + std::to_string(Counter++));
#endif

  if (Options.isDontTouchFunction(F.getName().str())) {
    DEBUG("Function is in dont-touch list, ignoring ...\n");
    return false;
  }
  // control-flow info
  DominatorTree DT(F);
  PostDominatorTree PDT(F);
  LoopInfo LI(DT);
  auto &TTI = FAM.getResult<TargetIRAnalysis>(F);

  // collect all valid branches
  SmallVector<BranchInst *> ValidBranches;
  for (BasicBlock &BB : F) {
    BranchInst *BI = dyn_cast<BranchInst>(BB.getTerminator());

    // if not a branch, ignore
    if (!BI)
      continue;
    // if not a conditional branch, ignore
    if (!BI->isConditional())
      continue;

    // only process basic blocks inside loops
    if (Options.OnlyInLoops && LI.getLoopFor(&BB) == nullptr)
      continue;

    // only process basic blocks with symbolic branches
    if (Options.OnlySymbolicBranches && !MSV.isSymbolic(*BI))
      continue;

    // if RunBrFusionOnly is set, only process diamond-shaped control-flow
    if (Options.OnlyMergeDiamond) {
      DEBUG("Cheking for dimanoind shaped control-flow ...\n");
      BasicBlock *LeftBlock = BI->getSuccessor(0);
      BasicBlock *RightBlock = BI->getSuccessor(1);
      BasicBlock *UniqSuccSuccL = LeftBlock->getUniqueSuccessor();
      BasicBlock *UniqSuccSuccR = RightBlock->getUniqueSuccessor();
      if (!UniqSuccSuccL || !UniqSuccSuccR || UniqSuccSuccL != UniqSuccSuccR) {
        DEBUG("Not a diamond-shaped branch, ignoring ...\n");
        continue;
      }
      DEBUG("Branch is diamond-shaped ...\n");

      if (containsSymbolicAddresses(LeftBlock, RightBlock, MSV)) {
        DEBUG(
            "Diamond control-flow contains symbolic addresses, ignoring ...\n");
        continue;
      }

      if (containsDontTouchLocs(LeftBlock, RightBlock, Options)) {
        DEBUG("Diamond control-flow contains dont-touch locations, ignoring "
              "...\n");
        continue;
      }

      // INFO("Valid branch found at block : " + BB.getName() + "\n");

      ValidBranches.push_back(BI);
    }
  }

  bool Changed = false;
  SmallVector<BasicBlock *> ModifiedBlocks;
  // now we try to apply CFMSE on each valid branch
  for (BranchInst *BI : ValidBranches) {
    BasicBlock *Block = BI->getParent();
    std::string BlockName = Block->getNameOrAsOperand();

    // decide if this a if-then or if-then-else merge
    BasicBlock *LeftBlock = BI->getSuccessor(0);
    BasicBlock *RightBlock = BI->getSuccessor(1);

    bool IsIfThen = LeftBlock->size() == 1 || RightBlock->size() == 1;

    DEBUG("Trying to apply CFMSE merge to block : " + BlockName + "\n");

    if (runCFMSE(Block, DT, PDT, TTI)) {
      DT.recalculate(F);
      PDT.recalculate(F);
      Changed = true;
      ModifiedBlocks.push_back(Block);
      NumCFMSEMerges++;

      NumIfThenMerges += IsIfThen;
      NumIfThenElseMerges += !IsIfThen;
      DEBUG("CFMSE merge applied to block : " + BlockName + "\n");
    }
  }

  // try to remove redundant jumps
  if (Changed) {
    removeRedundantJumps(ModifiedBlocks);
  }

  return Changed;
}

/**
static bool runCFMSEOnFunctionRecursive(Function &F,
                                              FunctionAnalysisManager &FAM,
                                              PreservedAnalyses &PA,
                                              CFMSEOptions &Options) {

  INFO << "Processing function : " << F.getName() << "\n";

  bool Changed = false, LocalChange = false;
  auto &TTI = FAM.getResult<TargetIRAnalysis>(F);

  // control-flow info
  DominatorTree DT(F);
  PostDominatorTree PDT(F);
  LoopInfo LI(DT);

  do {
    // compute symbolic variable analysis
    // SymbolicVariableAnalysis SV(*F.getParent(), GetAAResult);
    ModuleSymbolicVariableAnalysis MSV(*F.getParent(), FAM);
    LocalChange = false;

    for (BasicBlock &BB : F) {

      BranchInst *BI = dyn_cast<BranchInst>(BB.getTerminator());

      // if not a branch, ignore
      if (!BI)
        continue;
      // if not a conditional branch, ignore
      if (!BI->isConditional())
        continue;

      // only process basic blocks inside loops
      if (Options.OnlyInLoops && LI.getLoopFor(&BB) == nullptr)
        continue;

      // only process basic blocks with symbolic branches
      if (Options.OnlySymbolicBranches && !MSV.isSymbolic(*BI))
        continue;

      // if RunBrFusionOnly is set, only process diamond-shaped control-flow
      if (Options.OnlyMergeDiamond) {
        INFO << "Cheking for dimanoind shaped control-flow ...\n";
        BasicBlock *UniqSuccSuccL = BI->getSuccessor(0)->getUniqueSuccessor();
        BasicBlock *UniqSuccSuccR = BI->getSuccessor(1)->getUniqueSuccessor();
        if (!UniqSuccSuccL || !UniqSuccSuccR ||
            UniqSuccSuccL != UniqSuccSuccR) {
          INFO << "Not a diamond-shaped branch, ignoring ...\n";
          continue;
        }
        INFO << "Branch is diamond-shaped ...\n";
      }

      INFO << "Branch satisfying CFMSE constraints found at BB : "
           << BB.getNameOrAsOperand() << "\n";

      if (runCFMSE(&BB, DT, PDT, TTI)) {
        LocalChange = true;
        FAM.invalidate(F, PA);
        DT.recalculate(F);
        PDT.recalculate(F);
        LI = LoopInfo(DT);

        break;
      }
    }
    Changed = LocalChange | Changed;
  } while (LocalChange);

  return Changed;
}
**/

bool CFMSELegacyPass::runOnModule(Module &M) {
  INFO("CFMSELegacyPass is not implemented!\n");
  return false;
}

void CFMSELegacyPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<AAResultsWrapperPass>();
  AU.addRequired<TargetTransformInfoWrapperPass>();
}

void CFMSEOptions::setDontTouchLocs(const std::string &JsonFilePath) {

  if (JsonFilePath.size() == 0)
    return;

  std::ifstream ifs(JsonFilePath);
  json LocationsMap = json::parse(ifs);

  for (auto Filename : LocationsMap.items()) {
    for (auto FuncName : Filename.value().items()) {
      // this function is not touched
      if (FuncName.value() == "all") {
        std::string DontTouchFuncName = FuncName.key();
        DontTouchFunctions.insert(DontTouchFuncName);
        continue;
      }
      // specific locations are not touched
      for (std::string Loc : FuncName.value()) {
        std::string DontTouchLine = Filename.key() + "::" + Loc;
        DontTouchLocs.insert(DontTouchLine);
      }
    }
  }
}

PreservedAnalyses CFMSEPass::run(Module &M, ModuleAnalysisManager &AM) {
  FunctionAnalysisManager &FAM =
      AM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();
  PreservedAnalyses PA;

  auto GetAAForFunc = [&FAM](Function *F) -> AAResults & {
    return FAM.getResult<AAManager>(*F);
  };

  int preSelectInstructions = 0;
  int preCondBranches = 0;
  int preUnCondBranches = 0;
  int totalInstructionsBef = 0;
  int totalInstructionsAft = 0;


  // collect functions that should not be touched
  DenseSet<Function *> ExternFuncs;
  for (auto &F : M) {
    if (F.isDeclaration())
      continue;
    std::string FuncName = F.getName().str();
    std::string FileName = "";
    preSelectInstructions += countSelects(F);
    preCondBranches += countCondBranches(F);
    preUnCondBranches += countUnCondBranches(F);
    totalInstructionsBef += countTotalInstructions(F);
    if (F.getSubprogram()) {
      FileName = F.getSubprogram()->getFilename().str();
    }
    if (Options.isExternFuncOrFile(FuncName, FileName)) {
      ExternFuncs.insert(&F);
    }
  }

  if (CFMSEPrintSV) {
    ModuleSymbolicVariableAnalysis SV(M, FAM, ExternFuncs,
                                      Options.MarkAllLoadsSymbolic);
    SV.print(errs());
    return PA;
  }

  if (CFMSEPrintSVFunc != "") {
    ModuleSymbolicVariableAnalysis SV(M, FAM, ExternFuncs,
                                      Options.MarkAllLoadsSymbolic);
    SV.printForFunction(errs(), CFMSEPrintSVFunc);
    return PA;
  }

  if (RunCFMSEAnalysisOnly) {
    runAnalysisOnly(M, GetAAForFunc);
    return PA;
  }

  // overide cfmse options if command line options are set
  if (CFMSEDiamondOnly)
    Options.OnlyMergeDiamond = true;

  if (ForceCFMSE) {
    Options.OnlySymbolicBranches = false;
    Options.OnlyInLoops = false;
  }

  // strip non line debug info
  removeNonLineDebugInfo(M);

  // initialize the merged metadata
  DebugInfoMerger::getInstance().initializeMetadata(M);

  Type *CharArrayTy = ArrayType::get(Type::getInt8Ty(M.getContext()), 8);

  // add DCI gloabal byte array for DCI
  auto AddDCIGlobal = [&]() -> GlobalVariable * {
    auto *DCIGV = new GlobalVariable(
        M, CharArrayTy, false, GlobalValue::PrivateLinkage,
        ConstantAggregateZero::get(CharArrayTy), "cfmse.dci_gv");
    return DCIGV;
  };

  auto *DCIGV = AddDCIGlobal();
  DEBUG("DCI global : " + DCIGV->getName().str() + "\n");

  // add DCI gep instruction to entry block
  auto AddDCIGEP = [&](BasicBlock *EntryBlock) -> GetElementPtrInst * {
    GetElementPtrInst *DCIGEP = GetElementPtrInst::Create(
        CharArrayTy, &*DCIGV,
        {ConstantInt::get(Type::getInt64Ty(M.getContext()), 0),
         ConstantInt::get(Type::getInt64Ty(M.getContext()), 0)},
        "cfmse.dci_gep", EntryBlock->getTerminator());
    return DCIGEP;
  };

  // add DCI GEP for all functions
  for (Function &F : M) {
    if (F.isDeclaration())
      continue;
    if (ExternFuncs.count(&F)) {
      continue;
    }
    AddDCIGEP(&F.getEntryBlock());
  }

  bool Changed = false;

  INFO("Running CFMSE ...\n");
  INFO("Select Instructions before CFMSE : " +
       std::to_string(preSelectInstructions) + "\n");
  INFO("Cond Branch Instructions before CFMSE : " +
        std::to_string(preCondBranches) + "\n");
  INFO("Uncond Branch Instructions before CFMSE : " +
    std::to_string(preUnCondBranches) + "\n");
  INFO("Total Instructions before CFMSE : " +
        std::to_string(totalInstructionsBef) + "\n");
    
  do {
    // (re)-computing SVA
    ModuleSymbolicVariableAnalysis MSV(M, FAM, ExternFuncs,
                                       Options.MarkAllLoadsSymbolic);

    Changed = false;
    for (Function &F : M) {
      if (!F.isDeclaration()) {
        // ignore external function calls (libc calls etc.)
        if (ExternFuncs.count(&F)) {
          DEBUG("Function " + F.getName() +
                " is marked external. ignoring ...\n");
          continue;
        }
        // convert if-then to if-then-else first
        if (processOneSidedBranches(F)) {
          Changed = true;
          FAM.invalidate(F, PA);
        }

        // get the number of select instructions
        int NumSelectsBefore = countSelects(F);
        // run CFMSE
        if (runCFMSEOnFunction(F, FAM, PA, Options, MSV)) {
          Changed = true;
          FAM.invalidate(F, PA);
          NumSelectsAdded += countSelects(F) - NumSelectsBefore;
        }
      }
    }
  } while (Changed);

  // print some stats
  INFO("Number of successful applications of CFMSE : " +
       std::to_string(NumCFMSEMerges) + "\n");
  INFO("Number of if-then merges : " + std::to_string(NumIfThenMerges) + "\n");
  INFO("Number of if-then-else merges : " +
       std::to_string(NumIfThenElseMerges) + "\n");
  INFO("Number of select instructions added : " +
       std::to_string(NumSelectsAdded) + "\n");

  int postSelectInstructions = 0;
  int postCondBranches = 0;
  int postUnCondBranches = 0;
  for (Function &F : M) {
    if (!F.isDeclaration()) {
      postSelectInstructions += countSelects(F);
      postCondBranches += countCondBranches(F);
      postUnCondBranches += countUnCondBranches(F);
      totalInstructionsAft += countTotalInstructions(F);
    }
  }
  INFO("Select Instructions after CFMSE : " +
       std::to_string(postSelectInstructions) + "\n");

  INFO("Cond Branch Instructions after CFMSE : " +
        std::to_string(postCondBranches) + "\n");

  INFO("Uncond Branch Instructions after CFMSE : " +
    std::to_string(postUnCondBranches) + "\n");

  INFO("Total Instructions after CFMSE : " +
        std::to_string(totalInstructionsAft) + "\n");

  return PA;
}

char CFMSELegacyPass::ID = 0;
INITIALIZE_PASS_BEGIN(CFMSELegacyPass, "cfmse",
                      "contorl-flow meling for symbolic execution", false,
                      false)
INITIALIZE_PASS_DEPENDENCY(AAResultsWrapperPass)
INITIALIZE_PASS_DEPENDENCY(TargetTransformInfoWrapperPass)
INITIALIZE_PASS_END(CFMSELegacyPass, "cfmse",
                    "contorl-flow meling for symbolic execution", false, false)

ModulePass *llvm::createCFMSEPass() { return new CFMSELegacyPass(); }

void llvm::initializeCFMSE(PassRegistry &Registry) {
  initializeCFMSELegacyPassPass(Registry);
}

// remove all debug info except line table
bool llvm::removeNonLineDebugInfo(Module &M) {
  INFO("Removing non line table debug info ...\n");
  return stripNonLineTableDebugInfo(M);
}

PreservedAnalyses RemoveNonLineDebugInfoPass::run(Module &M,
                                                  ModuleAnalysisManager &AM) {
  PreservedAnalyses PA;
  removeNonLineDebugInfo(M);
  return PA;
}