#ifndef LLVM_TRANSFORMS_BB_REPLICATION_H
#define LLVM_TRANSFORMS_BB_REPLICATION_H

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"

namespace llvm {

class BBReplicationPass 
    : public PassInfoMixin<BBReplicationPass> {

public:
  PreservedAnalyses run(Function &, FunctionAnalysisManager&);
};

FunctionPass* createBBReplicationPass();

bool processOneSidedBranches(Function &F); 
} // end namespace llvm


#endif // LLVM_TRANSFORMS_CFMSE_LOCATION_ANALYSIS_H