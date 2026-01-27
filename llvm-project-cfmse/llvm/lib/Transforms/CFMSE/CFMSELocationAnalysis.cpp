#include "llvm/Transforms/CFMSE/CFMSELocationAnalysis.h"
#include "CFMSEUtils.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Registry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TableGen/Record.h"


using namespace llvm;

namespace {
class CFMSELocationAnalysisLegacyPass : public ModulePass {
public:
  static char ID;
  CFMSELocationAnalysisLegacyPass() : ModulePass(ID) {
    initializeCFMSELocationAnalysisLegacyPassPass(*PassRegistry::getPassRegistry());
  }

  bool runOnModule(Module &M) override;

  void getAnalysisUsage(AnalysisUsage &AU) const override;
};
} // namespace

bool CFMSELocationAnalysisLegacyPass::runOnModule(Module &M) {
  INFO("CFMSELocationAnalysisLegacyPass is not implemented!\n");
  return false;
}

void CFMSELocationAnalysisLegacyPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<AAResultsWrapperPass>();
  AU.addRequired<TargetTransformInfoWrapperPass>();
}

SmallVector<Function *> getRecursiveFunctions(Module &M) {
  SmallVector<Function *> List;

  //code goes here
  CallGraph CG(M);

  for(scc_iterator<CallGraph *> I = scc_begin(&CG); !I.isAtEnd(); ++I) {
    const std::vector<CallGraphNode *> &SCC = *I;

    if (SCC.size() > 1){ // mutually recursive functions
        for (const auto *C : SCC){
          Function * F = C->getFunction();
          if (F && !F->isDeclaration()){
            List.push_back(F);
          }
        }
    } else {
      if (SCC.size() == 1){ // self recursive functions
        const auto *N = SCC[0];
        Function * F = N->getFunction();
        if (F && !F->isDeclaration()){
          int Scalls = 0;
          for (auto C = CG[F]->begin(); C != CG[F]->end(); ++C){
            Function *Callee = C->second->getFunction();
            if (Callee && !Callee->isDeclaration() && 
                Callee->getName() == F->getName()) Scalls++;
          }
          if (Scalls > 0) {
              List.push_back(F);
          }
        }
      }
    }
  }
  return List;
}

PreservedAnalyses CFMSELocationAnalysisPass::run(Module &M, ModuleAnalysisManager &AM) {
  FunctionAnalysisManager &FAM =
      AM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();
  PreservedAnalyses PA;

  SmallVector<Function*> List = getRecursiveFunctions(M);

  DEBUG("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  DEBUG("Recursive Functions\n");
  DEBUG("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  for (auto *F:List)
    DEBUG("Function Name: " + F->getName().str() + "\n");
  DEBUG("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  return PA;
}

char CFMSELocationAnalysisLegacyPass::ID = 0;
INITIALIZE_PASS_BEGIN(CFMSELocationAnalysisLegacyPass, "cfmse-location",
                      "contorl-flow melding location for symbolic execution", false, true)
INITIALIZE_PASS_DEPENDENCY(AAResultsWrapperPass)
INITIALIZE_PASS_DEPENDENCY(TargetTransformInfoWrapperPass)
INITIALIZE_PASS_END(CFMSELocationAnalysisLegacyPass, "cfmse-location",
                    "contorl-flow melding location for symbolic execution", false, true)

ModulePass *llvm::createCFMSELocationAnalysisPass() { return new CFMSELocationAnalysisLegacyPass(); }

void llvm::initializeCFMSELocationAnalysis(PassRegistry &Registry) {
  initializeCFMSELocationAnalysisLegacyPassPass(Registry);
}