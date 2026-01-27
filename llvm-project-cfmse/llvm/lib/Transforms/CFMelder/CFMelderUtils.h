#ifndef LLVM_LIB_TRANSFORMS_CFMELDER_UTILS_H
#define LLVM_LIB_TRANSFORMS_CFMELDER_UTILS_H

// #include "llvm/ADT/SequenceAlignment.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/RegionInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

// #define CFMELDER_DEBUG

#define INFO(x) do { errs() << "INFO[cfmelder]: " << x; } while (0)


#ifdef CFMELDER_DEBUG

#define DEBUG(x) do { errs() << "DEBUG[cfmelder]: " << x; } while (0)

#else

#define DEBUG(x)

#endif

namespace llvm {

struct CFMInstructionCost {
  virtual int getCost(const Instruction *I) = 0;
  virtual int getBrCost() = 0;
};

/// utility functions
class Utils {
public:
  static bool containsUnhandledInstructions(const BasicBlock *BB);

  /// Check if block BB is valid location to apply the melding transformation.
  /// follwing condtions are checked here.
  /// - BB must have two successors
  /// - BB must dominate both successors
  /// - Successors of BB can not have a path between them
  /// - Successors of BB can not post-dominate each other
  /// - BB must have post dominator
  /// - Region encapsulated by BB and its post-dominator can not contain
  /// unhandled instructions
  ///   (currently switch instructions)  : FIXME
  static bool isValidMergeLocation(BasicBlock &BB, DominatorTree &DT,
                                   PostDominatorTree &PDT);

  /// Returns true if any of blocks L's predecessors are dominated by R
  /// or any of R's predecessors are dominated by L
  static bool hasPathBetween(BasicBlock *L, BasicBlock *R, DominatorTree &DT);

  /// Checks if value 'V1' can be merged with value 'V2'
  static bool match(Value *V1, Value *V2);

  /// Computes maximum possible latency reduction achieved by merging
  /// two blocks in the best case scenario (i.e. everything aligns)
  static std::pair<unsigned, unsigned>
  computeLatReductionAtBest(BasicBlock *BB1, BasicBlock *BB2,
                            CFMInstructionCost &InstructionCostModel);

  /// Compute the similarity score for two blocks
  static double
  computeBlockSimilarity(BasicBlock *BB1, BasicBlock *BB2,
                         CFMInstructionCost &InstructionCostModel);

  /// Compute block similarity with region replication
  static double
  computeBlockSimilarity(BasicBlock *BB1, BasicBlock *BB2, Region *Replicated,
                         CFMInstructionCost &InstructionCostModel);

  /// Computes the similarity score for two regions given by 'Mapping'
  static double
  computeRegionSimilarity(const DenseMap<BasicBlock *, BasicBlock *> &Mapping,
                          BasicBlock *LExit,
                          CFMInstructionCost &InstructionCostModel);

  /// Given a region tree, returns the region with entry 'Entry' and exit 'Exit'
  static Region *getRegionWithEntryExit(RegionInfo &RI, BasicBlock *Entry,
                                        BasicBlock *Exit);

  /// checks if a region need to be simplified. Region R is not simple if it's
  /// exit has predecessors from outside R
  static bool requireRegionSimplification(Region *R);

  // cutomized instruction latency cost for GPU
  static int getGPUInstructionCost(const Instruction *I);

  // cutomized instruction latency cost for symbolic execution
  static int getSEInstructionCost(const Instruction *I);

  // instruction cost for code size
  static int getCodeSizeInstructionCost(const Instruction *I,
                                        TargetTransformInfo &TTI);

  /// get name as operand for basic block
  static std::string getNameStr(Value *V);
};

} // namespace llvm

#endif