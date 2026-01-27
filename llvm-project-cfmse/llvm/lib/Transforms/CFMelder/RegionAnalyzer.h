#ifndef LLVM_LIB_TRANSFORMS_REGION_ANALYZER_H
#define LLVM_LIB_TRANSFORMS_REGION_ANALYZER_H

#include "CFMelderUtils.h"
#include "SeqAlignmentUtils.h"
#include "llvm/Analysis/DominanceFrontier.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/RegionInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/InstructionCost.h"
#include "llvm/Transforms/IPO/FunctionMerging.h"
#include <memory>

namespace llvm {

/// convienience object to pass control-flow info around
class ControlFlowGraphInfo {
private:
  Function &F;
  DominatorTree &DT;
  PostDominatorTree &PDT;
  TargetTransformInfo &TTI;
  std::shared_ptr<RegionInfo> RI;
  std::shared_ptr<LoopInfo> LI;

public:
  ControlFlowGraphInfo(Function &F, DominatorTree &DT, PostDominatorTree &PDT,
                       TargetTransformInfo &TTI);
  /// recompute analyses
  void recompute();
  ///
  Function &getFunction() { return F; }
  /// get dom tree
  DominatorTree &getDomTree() { return DT; }
  /// get post-dom tree
  PostDominatorTree &getPostDomTree() { return PDT; }
  /// get region info
  shared_ptr<RegionInfo> getRegionInfo() { return RI; }
  /// get loop info
  shared_ptr<LoopInfo> getLoopInfo() { return LI; }
  /// get TTI
  TargetTransformInfo &getTTI() { return TTI; }
};

class RegionComparator {
private:
  const Region *R1;
  const Region *R2;
  DenseMap<BasicBlock *, BasicBlock *> Mapping;

public:
  RegionComparator(const Region *R1, const Region *R2) : R1(R1), R2(R2) {}
  // compare two regions, return true if they have equal control flow
  bool compare();
  // get the region mapping if exists
  void getMapping(DenseMap<BasicBlock *, BasicBlock *> &Result);
};

class MergeableRegionPair {
private:
  // Region *R1, *R2; // R1 == left, R2 == right
  BasicBlock *LEntry = nullptr, *LExit = nullptr;
  BasicBlock *REntry = nullptr, *RExit = nullptr;
  double SimilarityScore{0.0};
  DenseMap<BasicBlock *, BasicBlock *> Mapping;

  // void CalculateSimilarityScore();

public:
  MergeableRegionPair(Region &R1, Region &R2, RegionComparator &Comparator,
                      double Score);

  double getSimilarityScore() const { return SimilarityScore; }

  bool operator<(const MergeableRegionPair &RegionPair) {
    return this->SimilarityScore < RegionPair.getSimilarityScore();
  }

  bool operator>(const MergeableRegionPair &RegionPair) {
    return this->SimilarityScore > RegionPair.getSimilarityScore();
  }

  bool operator==(const MergeableRegionPair &RegionPair) {
    return this->SimilarityScore == RegionPair.getSimilarityScore();
  }

  friend llvm::raw_ostream &operator<<(llvm::raw_ostream &OS,
                                       MergeableRegionPair &MRP) {
    OS << "[ Left entry : " << MRP.getLeftEntry()->getName()
       << ", Left exit : " << MRP.getLeftExit()->getName()
       << ", Right entry : " << MRP.getRightEntry()->getName()
       << ", Right exit : " << MRP.getRightExit()->getName() << " ]";
    return OS;
  }

  // returns true if R1 dominates other.R1 and R2 dominates other.R2
  // i.e. this and other can be independantly mergeable
  bool dominates(std::shared_ptr<MergeableRegionPair> &Other,
                 DominatorTree &DT);

  BasicBlock *getLeftEntry() { return LEntry; }
  BasicBlock *getLeftExit() { return LExit; }

  BasicBlock *getRightEntry() { return REntry; }
  BasicBlock *getRightExit() { return RExit; }

  // DenseMap<BasicBlock *, BasicBlock *>::iterator begin() {
  //   return Mapping.begin();
  // }
  // DenseMap<BasicBlock *, BasicBlock *>::iterator end() { return Mapping.end(); }

  // get the region mapping if exists
  DenseMap<BasicBlock *, BasicBlock *> &getMapping() { return Mapping; }

  BasicBlock *getMatchingRightBb(BasicBlock *BB);
};

// check the compatibility of two instructions for merging
class InstructionMatch {
public:
  static bool match(Value *V1, Value *V2) {
    if (isa<Instruction>(V1) && isa<Instruction>(V2)) {
      Instruction *I1 = dyn_cast<Instruction>(V1);
      Instruction *I2 = dyn_cast<Instruction>(V2);

      if (I1->getOpcode() == I2->getOpcode() &&
          I1->getOpcode() == Instruction::Br)
        return true;
    }
    return FunctionMerger::match(V1, V2);
  };
};

// instruction cost model for code size
struct CodeSizeInstructionCost : public CFMInstructionCost {
  TargetTransformInfo *TTI = nullptr;
  CodeSizeInstructionCost(TargetTransformInfo *TTI) : TTI(TTI) {}
  int getCost(const Instruction *I) override {
    return 1 + TTI->getInstructionCost(I, TTI::TargetCostKind::TCK_CodeSize)
        .getValue()
        .getValue();
  }
  int getBrCost() override {
    return 1 + TTI->getCFInstrCost(Instruction::Br,
                                   TTI::TargetCostKind::TCK_CodeSize)
                   .getValue()
                   .getValue();
  }
};

// instruction cost model for GPU latency
struct GPUInstructionCost : public CFMInstructionCost {
  int getCost(const Instruction *I) override {
    return Utils::getGPUInstructionCost(I);
  }
  int getBrCost() override { return 2; }
};

// instruction cost model for Symbolic execution
struct SEInstructionCost : public CFMInstructionCost {
  int getCost(const Instruction *I) override {
    return Utils::getSEInstructionCost(I);
  }
  int getBrCost() override { return 2; }
};

// simple scoring function for instruction alignment for synbvolic execution
// TODO : change latency numbers
struct AlignmentScoringFunc : public ScoringFunction<Value *> {
  CFMInstructionCost &InstrCostModel;

public:
  AlignmentScoringFunc(CFMInstructionCost &IC) : InstrCostModel(IC) {}
  int operator()(Value *V1, Value *V2) override {

    if (!InstructionMatch::match(V1, V2))
      return 0;

    int SavedCycles = 0;
    if (isa<Instruction>(V1)) {
      Instruction *I1 = dyn_cast<Instruction>(V1);
      SavedCycles = InstrCostModel.getCost(I1);
    } else if (isa<BasicBlock>(V1)) {
      SavedCycles = 3;
    }

    return SavedCycles;
  }
  int gap(int K) override { return InstrCostModel.getBrCost(); }
};

// what type of cost model to use
enum CostModelTy { CodeSize, Latency, SE };

// Profitability model for region alignment
struct RegionScoringFunc : public ScoringFunction<Region *> {
  CFMInstructionCost &InstrCostModel;

public:
  RegionScoringFunc(CFMInstructionCost &IC) : InstrCostModel(IC) {}
  int operator()(Region *R1, Region *R2) override {
    RegionComparator RC(R1, R2);
    if (!RC.compare())
      return 0;
    DenseMap<BasicBlock *, BasicBlock *> Mapping;
    RC.getMapping(Mapping);
    double Score =
        Utils::computeRegionSimilarity(Mapping, R1->getExit(), InstrCostModel);

    return (int)(Score * 100);
  }
  int gap(int K) override { return 0; }
};

// wrap the alignment computation in a class
// to reuse the fucntions in analysis and codegen satges
class RegionInstructionAlignment {
private:
  AlignedSeq<Value *> Result;
  TargetTransformInfo *TTI = nullptr;
  // unique_ptr<ScoringFunction<Value *>> ScoringFunc;
  unique_ptr<AlignmentScoringFunc> ScoringFunc;
  void linearizeBb(BasicBlock *BB, SmallVectorImpl<Value *> &LinearizedVals);
  AlignedSeq<Value *> computeBlockAlignment(BasicBlock *LeftBb,
                                            BasicBlock *RightBb);

public:
  RegionInstructionAlignment(CFMInstructionCost &IC) {
    ScoringFunc = make_unique<AlignmentScoringFunc>(IC);
  }

  void compute(DenseMap<BasicBlock *, BasicBlock *> BlockMap);
  void printStats(llvm::raw_ostream &OS);
  AlignedSeq<Value *> getResult() { return Result; }
};

// class to analyze merebale control-flow
class RegionAnalyzer {
private:
  CostModelTy CostModelToUse = CodeSize;
  /// functtion to get instruction cost according to the cost model
  unique_ptr<CFMInstructionCost> InstrCostModel;

  BasicBlock *DivergentBB;
  Value *DivergentCondition;
  ControlFlowGraphInfo &CFGInfo;

  // left path and right path regions
  SmallVector<Region *, 0> LeftRegions;
  SmallVector<Region *, 0> RightRegions;

  // best matching of regions
  SmallVector<std::shared_ptr<MergeableRegionPair>, 0> BestRegionMatch;
  // best mathcing basic blocks, if regions do not exist
  std::pair<BasicBlock *, BasicBlock *> BestBbMatch{nullptr, nullptr};
  bool HasBbMatch = false;
  double BestBbMatchSimilarityScore = 0.0;

  // DCI compatibility of regions
  SmallVector<bool> DCICompatibility;

  void findMergeableRegions(BasicBlock &BB);
  BasicBlock *findMostSimilarBb(BasicBlock *BB,
                                SmallVectorImpl<BasicBlock *> &Candidates);
  /// Find mergeable blocks in 'Regions' that are not contained inside local
  /// loops
  void findMergeableBBsInRegions(BasicBlock *From,
                                 SmallVectorImpl<Region *> &Regions,
                                 SmallVectorImpl<BasicBlock *> &MergeableBBs);

  void computeGreedyRegionMatch();
  void computeSARegionMatch();



public:
  RegionAnalyzer(BasicBlock *BB, ControlFlowGraphInfo &CFGInfo,
                 CostModelTy CostTy = CodeSize);

  void computeRegionMatch();

    // compute the DCI compatibility of all region matches
  void computeDCICompatibility();

  // region analyzer's result
  DenseMap<BasicBlock *, BasicBlock *> getRegionMatch(unsigned Index);
  std::pair<BasicBlock *, BasicBlock *>
  getRegionMatchEntryBlocks(unsigned Index);
  std::pair<BasicBlock *, BasicBlock *>
  getRegionMatchExitBlocks(unsigned Index);
  // bool isInsideRegionMatch(BasicBlock *BB, unsigned Index);
  bool hasAnyProfitableMatch();
  bool isRegionMatchProfitable(unsigned Index);
  unsigned regionMatchSize() const;
  unsigned getMostProfitableRegionMatchIndex();

  // check compatibility for DCI
  bool isRegionMatchCompatibleForDCI(unsigned Index);

  // region replication, only applicable for BB-region melding
  bool requireRegionReplication();

  bool requireRegionSimplification(Region *R);

  /// infomation about divergent region
  Value *getDivergentCondition() const { return DivergentCondition; }

  BasicBlock *getDivergentBlock() const { return DivergentBB; }

  Function *getParentFunction() const {
    return getDivergentBlock()->getParent();
  }

  /// control-flow analysis
  ControlFlowGraphInfo &getCFGInfo() { return CFGInfo; }

  /// get instruction cost model
  CFMInstructionCost &getInstrCostModel() const { return *InstrCostModel; }

  void printAnalysis(llvm::raw_ostream &OS);
};

} // namespace llvm

#endif