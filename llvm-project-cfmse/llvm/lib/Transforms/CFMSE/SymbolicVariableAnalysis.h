#ifndef LLVM_LIB_TRANSFORMS_CFMELDER_SYM_VAR_ANALYSIS_
#define LLVM_LIB_TRANSFORMS_CFMELDER_SYM_VAR_ANALYSIS_
// #include "llvm/ADT/DenseSet.h"
// #include "llvm/Analysis/AliasAnalysis.h"
// #include "llvm/IR/InstIterator.h"
// #include "llvm/IR/Instruction.h"
// #include "llvm/IR/Instructions.h"
// #include "llvm/IR/Module.h"
// #include "llvm/IR/PassManager.h"

// namespace llvm {

// class SymbolicPropagator {

//   DenseSet<const Value *> SymbolicValues;

//   std::vector<const Value *> WorkList;

//   const Module *M;

//   function_ref<AAResults &(Function *F)> GetAAResult;

//   void markSymbolicVarargFunc(Function* VarargFunc);

// public:
//   SymbolicPropagator(Module &M,
//                      function_ref<AAResults &(Function *F)> GetAAResult)
//       : M(&M), GetAAResult(GetAAResult) {}

//   void compute();

//   bool isSymbolic(const Value *V) { return SymbolicValues.count(V) == 1; }

//   bool markSymbolic(const Value *V);

//   const Module *getModule() const { return M; }
// };

// class SymbolicVariableAnalysis {
//   SymbolicPropagator SP;

// public:
//   SymbolicVariableAnalysis(Module &M,
//                            function_ref<AAResults &(Function *F)>
//                            GetAAResult);

//   bool isSymbolic(const Value *V) { return SP.isSymbolic(V); }

//   bool isConcrete(const Value *V) { return !isSymbolic(V); }

//   void print(raw_ostream &OS);
// };

// } // namespace llvm

#include "llvm/ADT/DenseSet.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/SyncDependenceAnalysis.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <vector>

namespace llvm {
class Module;
class Value;
class Instruction;
class Loop;
class raw_ostream;
class TargetTransformInfo;

/// \brief Generic Symbolic analysis for reducible CFGs.
///
/// This analysis propagates Symbolic in a data-parallel context from sources
/// of Symbolic to all users. It requires reducible CFGs. All assignments
/// should be in SSA form.
class SymbolicVariableAnalysisImpl {
public:
  /// \brief This instance will analyze the whole function \p F or the loop \p
  /// RegionLoop.
  ///
  /// \param RegionLoop if non-null the analysis is restricted to \p RegionLoop.
  /// Otherwise the whole function is analyzed.
  /// \param IsLCSSAForm whether the analysis may assume that the IR in the
  /// region in in LCSSA form.
  SymbolicVariableAnalysisImpl(const Function &F, const Loop *RegionLoop,
                               const DominatorTree &DT, const LoopInfo &LI,
                               SyncDependenceAnalysis &SDA, bool IsLCSSAForm);

  /// \brief The loop that defines the analyzed region (if any).
  const Loop *getRegionLoop() const { return RegionLoop; }
  const Function &getFunction() const { return F; }

  /// \brief Whether \p BB is part of the region.
  bool inRegion(const BasicBlock &BB) const;
  /// \brief Whether \p I is part of the region.
  bool inRegion(const Instruction &I) const;

  /// \brief Mark \p UniVal as a value that is always uniform.
  void addUniformOverride(const Value &UniVal);

  /// \brief Mark \p DivVal as a value that is always Symbolic. Will not do so
  /// if `isAlwaysUniform(DivVal)`.
  /// \returns Whether the tracked Symbolic state of \p DivVal changed.
  bool markSymbolic(const Value &DivVal);

  /// \brief Propagate Symbolic to all instructions in the region.
  /// Symbolic is seeded by calls to \p markSymbolic.
  void compute();

  /// \brief Whether any value was marked or analyzed to be Symbolic.
  bool hasDetectedSymbolic() const { return !SymbolicValues.empty(); }

  /// \brief Whether \p Val will always return a uniform value regardless of its
  /// operands
  bool isAlwaysUniform(const Value &Val) const;

  /// \brief Whether \p Val is Symbolic at its definition.
  bool isSymbolic(const Value &Val) const;

  /// \brief Whether \p U is Symbolic. Uses of a uniform value can be
  /// Symbolic.
  bool isSymbolicUse(const Use &U) const;

private:
  /// \brief Mark \p Term as Symbolic and push all Instructions that become
  /// Symbolic as a result on the worklist.
  void analyzeControlSymbolic(const Instruction &Term);
  /// \brief Mark all phi nodes in \p JoinBlock as Symbolic and push them on
  /// the worklist.
  void taintAndPushPhiNodes(const BasicBlock &JoinBlock);

  /// \brief Identify all Instructions that become Symbolic because \p DivExit
  /// is a Symbolic loop exit of \p DivLoop. Mark those instructions as
  /// Symbolic and push them on the worklist.
  void propagateLoopExitSymbolic(const BasicBlock &DivExit,
                                 const Loop &DivLoop);

  /// \brief Internal implementation function for propagateLoopExitSymbolic.
  void analyzeLoopExitSymbolic(const BasicBlock &DivExit,
                               const Loop &OuterDivLoop);

  /// \brief Mark all instruction as Symbolic that use a value defined in \p
  /// OuterDivLoop. Push their users on the worklist.
  void analyzeTemporalSymbolic(const Instruction &I, const Loop &OuterDivLoop);

  /// \brief Push all users of \p Val (in the region) to the worklist.
  void pushUsers(const Value &I);

  /// \brief Whether \p Val is Symbolic when read in \p ObservingBlock.
  bool isTemporalSymbolic(const BasicBlock &ObservingBlock,
                          const Value &Val) const;

private:
  const Function &F;
  // If regionLoop != nullptr, analysis is only performed within \p RegionLoop.
  // Otherwise, analyze the whole function
  const Loop *RegionLoop;

  const DominatorTree &DT;
  const LoopInfo &LI;

  // Recognized Symbolic loops
  DenseSet<const Loop *> SymbolicLoops;

  // The SDA links Symbolic branches to Symbolic control-flow joins.
  SyncDependenceAnalysis &SDA;

  // Use simplified code path for LCSSA form.
  bool IsLCSSAForm;

  // Set of known-uniform values.
  DenseSet<const Value *> UniformOverrides;

  // Detected/marked Symbolic values.
  DenseSet<const Value *> SymbolicValues;

  // Internal worklist for Symbolic propagation.
  std::vector<const Instruction *> Worklist;
};

class SymbolicSourcesInfo {
  Function *F = nullptr;
  StructType *VaListTy = nullptr;
  AAResults &AA;
  bool MarkAllLoadsSymbolic = false;

  DenseSet<const Value *> SymbolicSources;

public:
  SymbolicSourcesInfo(Function &F, AAResults &AA,
                      bool MarkAllLoadsSymbolic);

  bool isSymbolicSource(const Value *I) const {
    return SymbolicSources.count(I) > 0;
  }

  bool markSymbolicSource(const Value *Source);

  bool markSymbolicVarargFunc();
};

class SymbolicVariableInfo {
  const Function &F;

  // If the function contains an irreducible region the Symbolic
  // analysis can run indefinitely. We set ContainsIrreducible and no
  // analysis is actually performed on the function. All values in
  // this function are conservatively reported as Symbolic instead.
  bool ContainsIrreducible;
  std::unique_ptr<SyncDependenceAnalysis> SDA;
  std::unique_ptr<SymbolicVariableAnalysisImpl> DA;

public:
  SymbolicVariableInfo(const Function &F, const DominatorTree &DT,
                       const PostDominatorTree &PDT, const LoopInfo &LI,
                       bool KnownReducible);

  /// Whether any Symbolic was detected.
  bool hasSymbolic() const {
    return ContainsIrreducible || DA->hasDetectedSymbolic();
  }

  /// The GPU kernel this analysis result is for
  const Function &getFunction() const { return F; }

  /// Whether \p V is Symbolic at its definition.
  bool isSymbolic(const Value &V) const {
    return ContainsIrreducible || DA->isSymbolic(V);
  }

  /// Whether \p U is Symbolic. Uses of a uniform value can be Symbolic.
  bool isSymbolicUse(const Use &U) const {
    return ContainsIrreducible || DA->isSymbolicUse(U);
  }

  /// Whether \p V is uniform/non-Symbolic.
  bool isUniform(const Value &V) const { return !isSymbolic(V); }

  /// Whether \p U is uniform/non-Symbolic. Uses of a uniform value can be
  /// Symbolic.
  bool isUniformUse(const Use &U) const { return !isSymbolicUse(U); }

  void compute(const SymbolicSourcesInfo &SSI);
};

class ModuleSymbolicVariableAnalysis {
  Module &M;
  DenseSet<Function*> FuncsToAnalyze;
  DenseMap<const Function *, std::unique_ptr<SymbolicVariableInfo>>
      ModuleSymbolicInfo;
  DenseMap<const Function *, std::unique_ptr<SymbolicSourcesInfo>>
      ModuleSymbolicSourcesInfo;
  DenseSet<const Function *> FunctionWorklist;

  bool MarkAllLoadsSymbolic = false;

public:
  ModuleSymbolicVariableAnalysis(Module &M, FunctionAnalysisManager &FAM, DenseSet<Function *> &DontAnalyze,
                                 bool MarkAllLoadsSymbolic);

  bool isSymbolic(const Value &V);

  void print(raw_fd_ostream &OS);

  void printForFunction(raw_fd_ostream &OS, const std::string &FuncName);
};

// /// \brief Symbolic analysis frontend for GPU kernels.
// class SymbolicAnalysis : public AnalysisInfoMixin<SymbolicAnalysis> {
//   friend AnalysisInfoMixin<SymbolicAnalysis>;

//   static AnalysisKey Key;

// public:
//   using Result = SymbolicVariableInfo;

//   /// Runs the Symbolic analysis on @F, a GPU kernel
//   Result run(Function &F, FunctionAnalysisManager &AM);
// };

// /// Printer pass to dump Symbolic analysis results.
// struct SymbolicAnalysisPrinterPass
//     : public PassInfoMixin<SymbolicAnalysisPrinterPass> {
//   SymbolicAnalysisPrinterPass(raw_ostream &OS) : OS(OS) {}

//   PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);

// private:
//   raw_ostream &OS;
// }; // class SymbolicAnalysisPrinterPass

} // namespace llvm

#endif