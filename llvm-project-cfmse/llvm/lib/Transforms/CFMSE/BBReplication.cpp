#include "llvm/Transforms/CFMSE/BBReplication.h"
#include "CFMSEUtils.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/Analysis/CFGPrinter.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/PassRegistry.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Registry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TableGen/Record.h"
#include "llvm/Transforms/CFMelder/CFMelder.h"
#include <string>

// #define ONESIZED_BRANCHES_DEBUG

using namespace llvm;

namespace {
class BBReplicationLegacyPass : public FunctionPass {
public:
  static char ID;
  BBReplicationLegacyPass() : FunctionPass(ID) {
    initializeBBReplicationLegacyPassPass(*PassRegistry::getPassRegistry());
  }

  bool runOnFunction(Function &F) override;

  void getAnalysisUsage(AnalysisUsage &AU) const override;
};
} // namespace

bool BBReplicationLegacyPass::runOnFunction(Function &F) {
  INFO("BBReplicationLegacyPass is not implemented\n");
  return false;
}

void BBReplicationLegacyPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<AAResultsWrapperPass>();
  AU.addRequired<TargetTransformInfoWrapperPass>();
  AU.addRequired<LoopInfoWrapperPass>();
}

bool llvm::processOneSidedBranches(Function &F) {

#ifdef ONESIZED_BRANCHES_DEBUG
  static int Counter = 0;
  writeCFGToDotFile(F, "before_one_sided_branches_" + std::to_string(Counter++));
#endif
  DominatorTree DT(F);
  LoopInfo LI(DT);
  // helper to add a dummy basic block to convert if-then to if-then-else
  auto ConvertToDiamond = [&](BranchInst *BI,
                              BasicBlock *FallThroughBB) -> BasicBlock * {
    BasicBlock *NewBb = BasicBlock::Create(F.getContext(), "replicated.bb", &F);
    BranchInst::Create(FallThroughBB, NewBb);
    unsigned SuccIdx = BI->getSuccessor(0) == FallThroughBB ? 0 : 1;
    BI->setSuccessor(SuccIdx, NewBb);
    // fix phi node for new replicated bb successor
    for (auto &PHI : FallThroughBB->phis()) {
      PHI.replaceIncomingBlockWith(BI->getParent(), NewBb);
    }
    return NewBb;
  };

  // if then block contains side effects, we cannot replicate it
  // eg. call, invoke, etc.
  auto ContainsSideEffects = [&](BasicBlock *BB) -> bool {
    for (auto &I : *BB) {
      unsigned int OpCode = I.getOpcode();
      if (OpCode == Instruction::Call || OpCode == Instruction::Invoke)
        return true;
    }
    return false;
  };

  SmallVector<std::pair<BranchInst *, BasicBlock *>> BranchesToProcess;

  for (BasicBlock &Block : F) {
    for (Instruction &I : Block) {
      if (auto *BI = dyn_cast<BranchInst>(&I)) {
        if (BI->isConditional()) {
          BasicBlock *TrueBlock = BI->getSuccessor(0);
          BasicBlock *FalseBlock = BI->getSuccessor(1);
          BasicBlock *ThenBlock = nullptr;
          BasicBlock *CommonSucc = nullptr;
          // process one sided branches,
          // with true block on LHS
          if (TrueBlock->getSinglePredecessor() != nullptr &&
              FalseBlock->getSinglePredecessor() == nullptr) {
            ThenBlock = TrueBlock;
            CommonSucc = FalseBlock;
          }
          // Or true block on RHS
          else if (FalseBlock->getSinglePredecessor() != nullptr &&
                   TrueBlock->getSinglePredecessor() == nullptr) {
            ThenBlock = FalseBlock;
            CommonSucc = TrueBlock;
          }

          // then block must have a single successor and it must be common 
          // to then block and branching block
          if (ThenBlock && ThenBlock->getSingleSuccessor() == CommonSucc)
            BranchesToProcess.push_back(std::make_pair(BI, ThenBlock));
        }
      }
    }
  }

  if (BranchesToProcess.empty())
    return false;

  bool Changed = false;
  for (auto &B : BranchesToProcess) {
    BranchInst *BI = B.first;
    BasicBlock *ThenBlock = B.second;
    if (ThenBlock && !ContainsSideEffects(ThenBlock)) {
      DEBUG("Found then block "  + ThenBlock->getNameOrAsOperand() +  "\n");
      BasicBlock *TrueBlock = BI->getSuccessor(0);
      BasicBlock *FalseBlock = BI->getSuccessor(1);
      auto *EleseBlock =
          ConvertToDiamond(BI, ThenBlock == TrueBlock ? FalseBlock : TrueBlock);
      DEBUG("Added new else block " + EleseBlock->getNameOrAsOperand() + "\n");
      Changed = true;
    }
  }

#ifdef ONESIZED_BRANCHES_DEBUG
  if (Changed)
    writeCFGToDotFile(F, "after_one_sided_branches_" + std::to_string(Counter++));
#endif
  return Changed;
}

PreservedAnalyses BBReplicationPass::run(Function &F,
                                         FunctionAnalysisManager &FAM) {
  PreservedAnalyses PA;


  DEBUG("Processing function for BB Replication Pass : " + F.getName() +"\n");
  if (processOneSidedBranches(F))
    return PreservedAnalyses::none();

  return PA;
}

char BBReplicationLegacyPass::ID = 0;
INITIALIZE_PASS_BEGIN(BBReplicationLegacyPass, "bb-replication",
                      "complete the one-sided branches inside loops", false,
                      false)
INITIALIZE_PASS_DEPENDENCY(AAResultsWrapperPass)
INITIALIZE_PASS_DEPENDENCY(TargetTransformInfoWrapperPass)
INITIALIZE_PASS_DEPENDENCY(LoopInfoWrapperPass)
INITIALIZE_PASS_END(BBReplicationLegacyPass, "bb-replication",
                    "complete the one-sided branches inside loops", false,
                    false)

FunctionPass *llvm::createBBReplicationPass() {
  return new BBReplicationLegacyPass();
}

void llvm::initializeBBReplication(PassRegistry &Registry) {
  initializeBBReplicationLegacyPassPass(Registry);
}