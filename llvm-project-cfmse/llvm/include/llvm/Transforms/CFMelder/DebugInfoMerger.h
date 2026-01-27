#ifndef __LLVM_TRANSFORMS_DEBUG_INFO_MERGER_H__
#define __LLVM_TRANSFORMS_DEBUG_INFO_MERGER_H__

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include <string>

// #define DEBUG_INFO_MERGER_DEBUG

namespace llvm {

class DebugInfoMerger {
private:
  DebugInfoMerger() {}
  DebugInfoMerger(const DebugInfoMerger &) = delete;
  DebugInfoMerger &operator=(const DebugInfoMerger &) = delete;

  void initializeMetadata(Function &F);

  void printMetadata(const Function &F);
public:
  static DebugInfoMerger &getInstance() {
    static DebugInfoMerger DIM;
    return DIM;
  }
  // prints out info tracked by debug info merger
  void printMetadata(const Module &M);
  // adds custom metadata to function
  void initializeMetadata(Module &M);
  // update custom metadata for a merged instruction pair
  void updateMetaData(Instruction *LeftI, Instruction *RightI,
                      Instruction *MergedI);

};
} // namespace llvm

#endif