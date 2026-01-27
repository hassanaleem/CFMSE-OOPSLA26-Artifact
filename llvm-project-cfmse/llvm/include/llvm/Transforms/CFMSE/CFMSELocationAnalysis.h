#ifndef LLVM_TRANSFORMS_CFMSE_LOCATION_ANALYSIS_H
#define LLVM_TRANSFORMS_CFMSE_LOCATION_ANALYSIS_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class CFMSELocationAnalysisPass
    : public PassInfoMixin<CFMSELocationAnalysisPass> {

public:
  PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

ModulePass* createCFMSELocationAnalysisPass();

} // end namespace llvm


#endif // LLVM_TRANSFORMS_CFMSE_LOCATION_ANALYSIS_H