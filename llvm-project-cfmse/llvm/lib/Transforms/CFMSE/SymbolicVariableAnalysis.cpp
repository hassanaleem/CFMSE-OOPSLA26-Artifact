// #include "SymbolicVariableAnalysis.h"
// #include "CFMSEUtils.h"
// #include "llvm/IR/DerivedTypes.h"
// #include "llvm/IR/GlobalVariable.h"
// #include "llvm/IR/Instructions.h"
// #include "llvm/Support/raw_ostream.h"

// using namespace llvm;

// bool SymbolicPropagator::markSymbolic(const Value *V) {
//   return SymbolicValues.insert(V).second;
// }

// void SymbolicPropagator::compute() {

//   for (const Value *V : SymbolicValues) {
//     WorkList.push_back(V);
//   }

//   while (!WorkList.empty()) {
//     const Value *I = WorkList.back();
//     WorkList.pop_back();

//     for (const User *U : I->users()) {
//       const Instruction *UserI = dyn_cast<Instruction>(U);
//       if (!UserI)
//         continue;

//       if (markSymbolic(UserI)) {
//         // if the user is a function call, mark the argument as symbolic
//         if (const CallInst *CI = dyn_cast<const CallInst>(UserI)) {
//           // obtain operand number of instruction I in this user
//           unsigned OpNum = 0;
//           for (unsigned Op = 0; Op < UserI->getNumOperands(); Op++) {
//             if (UserI->getOperand(Op) == I) {
//               OpNum = Op;
//               break;
//             }
//           }
//           Function *CalledFunc = CI->getCalledFunction();
//           // if this is a
//           if(CalledFunc != NULL) {
//             if (OpNum < CalledFunc->arg_size()) {
//             // mark the argument as symbolic
//             Argument *SymbolicArg = CalledFunc->getArg(OpNum);
//             markSymbolic(SymbolicArg);
//             WorkList.push_back(SymbolicArg);

//             } else {
//               DEBUG << "Call to vaarg function found! Marking all varargs as
//               symbolic! \n"; markSymbolicVarargFunc(CalledFunc);
//             }
//           }
//         }
//         // storing symbolic value to an address
//         else if (const StoreInst *SI = dyn_cast<StoreInst>(UserI)) {
//           if (isSymbolic(SI->getValueOperand())) {
//             markSymbolic(SI->getPointerOperand());
//             WorkList.push_back(SI->getPointerOperand());
//           }
//         }

//         WorkList.push_back(UserI);
//       }
//     }
//   }
// }

// void SymbolicPropagator::markSymbolicVarargFunc(Function *VarargFunc) {

//   // find the struct type of va_list_tag and find any alloca instruction that
//   // use this type as its element type. Mark them as symbolic.
//   for (auto &StructTy : M->getIdentifiedStructTypes()) {
//     if (StructTy->getName().startswith("struct.__va_list_tag")) {
//       for (Instruction &I : instructions(*VarargFunc)) {
//         if (AllocaInst *AI = dyn_cast<AllocaInst>(&I)) {
//           if (AI->getAllocatedType()->isArrayTy() &&
//               AI->getAllocatedType()->getArrayElementType() == StructTy) {
//             markSymbolic(AI);
//             WorkList.push_back(AI);
//           }
//         }
//       }
//     }
//   }
// }

// void SymbolicVariableAnalysis::print(raw_ostream &OS) {
//   for (const Function &F : *SP.getModule()) {
//     // OS << "Function name : " << F.getName() << "\n";
//     for (const Instruction &I : instructions(F)) {
//       I.print(OS);
//       OS << " : " << (SP.isSymbolic(&I) ? "Symbolic" : "Concrete") << "\n";
//     }
//   }
// }

// SymbolicVariableAnalysis::SymbolicVariableAnalysis(
//     Module &M, function_ref<AAResults &(Function *F)> GetAAResult)
//     : SP(M, GetAAResult) {

//   // mark all symbolic sources
//   for (Function &F : M) {

//     if (F.isDeclaration())
//       continue;

//     // mark all arguments of main function as symbolic
//     if (F.getName() == "main") {
//       for (Argument &Arg : F.args()) {
//         SP.markSymbolic(&Arg);
//       }
//     }

//     for (const Instruction &I : instructions(F)) {
//       if (const CallInst *CI = dyn_cast<CallInst>(&I)) {

//         // ignore indirect calls or calls to inline assembly
//         if (CI->isIndirectCall() || CI->isInlineAsm()) {
//           continue;
//         }
//         // klee_make_symbolic function creates a symbolic variable
//         Function *CalledFunc = CI->getCalledFunction();
//         if (CalledFunc &&
//         CalledFunc->getName().contains("klee_make_symbolic")) {
//           const Value *VoidPtrArg = CI->getOperand(0);
//           AAResults &AA = GetAAResult(&F);

//           // any instruction that alias with this void ptr is a symbolic
//           source for (const Instruction &OtherI : instructions(F)) {
//             if (VoidPtrArg == &OtherI)
//               continue;
//             auto Result = AA.alias(VoidPtrArg, &OtherI);
//             if (Result == AliasResult::MustAlias) {
//               SP.markSymbolic(&OtherI);
//             }
//           }
//         }
//       }
//     }
//   }
//   SP.compute();
// }

//===---- DivergenceAnalysis.cpp --- Divergence Analysis Implementation ----==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements a general divergence analysis for loop vectorization
// and GPU programs. It determines which branches and values in a loop or GPU
// program are divergent. It can help branch optimizations such as jump
// threading and loop unswitching to make better decisions.
//
// GPU programs typically use the SIMD execution model, where multiple threads
// in the same execution group have to execute in lock-step. Therefore, if the
// code contains divergent branches (i.e., threads in a group do not agree on
// which path of the branch to take), the group of threads has to execute all
// the paths from that branch with different subsets of threads enabled until
// they re-converge.
//
// Due to this execution model, some optimizations such as jump
// threading and loop unswitching can interfere with thread re-convergence.
// Therefore, an analysis that computes which branches in a GPU program are
// divergent can help the compiler to selectively run these optimizations.
//
// This implementation is derived from the Vectorization Analysis of the
// Region Vectorizer (RV). That implementation in turn is based on the approach
// described in
//
//   Improving Performance of OpenCL on CPUs
//   Ralf Karrenberg and Sebastian Hack
//   CC '12
//
// This implementation is generic in the sense that it does
// not itself identify original sources of divergence.
// Instead specialized adapter classes, (LoopDivergenceAnalysis) for loops and
// (DivergenceAnalysis) for functions, identify the sources of divergence
// (e.g., special variables that hold the thread ID or the iteration variable).
//
// The generic implementation propagates divergence to variables that are data
// or sync dependent on a source of divergence.
//
// While data dependency is a well-known concept, the notion of sync dependency
// is worth more explanation. Sync dependence characterizes the control flow
// aspect of the propagation of branch divergence. For example,
//
//   %cond = icmp slt i32 %tid, 10
//   br i1 %cond, label %then, label %else
// then:
//   br label %merge
// else:
//   br label %merge
// merge:
//   %a = phi i32 [ 0, %then ], [ 1, %else ]
//
// Suppose %tid holds the thread ID. Although %a is not data dependent on %tid
// because %tid is not on its use-def chains, %a is sync dependent on %tid
// because the branch "br i1 %cond" depends on %tid and affects which value %a
// is assigned to.
//
// The sync dependence detection (which branch induces divergence in which join
// points) is implemented in the SyncDependenceAnalysis.
//
// The current implementation has the following limitations:
// 1. intra-procedural. It conservatively considers the arguments of a
//    non-kernel-entry function and the return value of a function call as
//    divergent.
// 2. memory as black box. It conservatively considers values loaded from
//    generic or local address as divergent. This can be improved by leveraging
//    pointer analysis and/or by modelling non-escaping memory objects in SSA
//    as done in RV.
//
//===----------------------------------------------------------------------===//

#include "SymbolicVariableAnalysis.h"
#include "CFMSEUtils.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>

using namespace llvm;

#define DEBUG_TYPE "divergence"

SymbolicVariableAnalysisImpl::SymbolicVariableAnalysisImpl(
    const Function &F, const Loop *RegionLoop, const DominatorTree &DT,
    const LoopInfo &LI, SyncDependenceAnalysis &SDA, bool IsLCSSAForm)
    : F(F), RegionLoop(RegionLoop), DT(DT), LI(LI), SDA(SDA),
      IsLCSSAForm(IsLCSSAForm) {}

bool SymbolicVariableAnalysisImpl::markSymbolic(const Value &DivVal) {
  if (isAlwaysUniform(DivVal))
    return false;
  assert(isa<Instruction>(DivVal) || isa<Argument>(DivVal));
  assert(!isAlwaysUniform(DivVal) && "cannot be a divergent");
  return SymbolicValues.insert(&DivVal).second;
}

void SymbolicVariableAnalysisImpl::addUniformOverride(const Value &UniVal) {
  UniformOverrides.insert(&UniVal);
}

bool SymbolicVariableAnalysisImpl::isTemporalSymbolic(
    const BasicBlock &ObservingBlock, const Value &Val) const {
  const auto *Inst = dyn_cast<const Instruction>(&Val);
  if (!Inst)
    return false;
  // check whether any divergent loop carrying Val terminates before control
  // proceeds to ObservingBlock
  for (const auto *Loop = LI.getLoopFor(Inst->getParent());
       Loop != RegionLoop && !Loop->contains(&ObservingBlock);
       Loop = Loop->getParentLoop()) {
    if (SymbolicLoops.contains(Loop))
      return true;
  }

  return false;
}

bool SymbolicVariableAnalysisImpl::inRegion(const Instruction &I) const {
  return I.getParent() && inRegion(*I.getParent());
}

bool SymbolicVariableAnalysisImpl::inRegion(const BasicBlock &BB) const {
  return (!RegionLoop && BB.getParent() == &F) || RegionLoop->contains(&BB);
}

void SymbolicVariableAnalysisImpl::pushUsers(const Value &V) {
  const auto *I = dyn_cast<const Instruction>(&V);

  if (I && I->isTerminator()) {
    analyzeControlSymbolic(*I);
    return;
  }

  for (const auto *User : V.users()) {
    const auto *UserInst = dyn_cast<const Instruction>(User);
    if (!UserInst)
      continue;

    // only compute divergent inside loop
    if (!inRegion(*UserInst))
      continue;

    // All users of divergent values are immediate divergent
    if (markSymbolic(*UserInst))
      Worklist.push_back(UserInst);
  }
}

static const Instruction *getIfCarriedInstruction(const Use &U,
                                                  const Loop &DivLoop) {
  const auto *I = dyn_cast<const Instruction>(&U);
  if (!I)
    return nullptr;
  if (!DivLoop.contains(I))
    return nullptr;
  return I;
}

void SymbolicVariableAnalysisImpl::analyzeTemporalSymbolic(
    const Instruction &I, const Loop &OuterDivLoop) {
  if (isAlwaysUniform(I))
    return;
  if (isSymbolic(I))
    return;

  LLVM_DEBUG(dbgs() << "Analyze temporal divergence: " << I.getName() << "\n");
  assert((isa<PHINode>(I) || !IsLCSSAForm) &&
         "In LCSSA form all users of loop-exiting defs are Phi nodes.");
  for (const Use &Op : I.operands()) {
    const auto *OpInst = getIfCarriedInstruction(Op, OuterDivLoop);
    if (!OpInst)
      continue;
    if (markSymbolic(I))
      pushUsers(I);
    return;
  }
}

// marks all users of loop-carried values of the loop headed by LoopHeader as
// divergent
void SymbolicVariableAnalysisImpl::analyzeLoopExitSymbolic(
    const BasicBlock &DivExit, const Loop &OuterDivLoop) {
  // All users are in immediate exit blocks
  if (IsLCSSAForm) {
    for (const auto &Phi : DivExit.phis()) {
      analyzeTemporalSymbolic(Phi, OuterDivLoop);
    }
    return;
  }

  // For non-LCSSA we have to follow all live out edges wherever they may lead.
  const BasicBlock &LoopHeader = *OuterDivLoop.getHeader();
  SmallVector<const BasicBlock *, 8> TaintStack;
  TaintStack.push_back(&DivExit);

  // Otherwise potential users of loop-carried values could be anywhere in the
  // dominance region of DivLoop (including its fringes for phi nodes)
  DenseSet<const BasicBlock *> Visited;
  Visited.insert(&DivExit);

  do {
    auto *UserBlock = TaintStack.pop_back_val();

    // don't spread divergence beyond the region
    if (!inRegion(*UserBlock))
      continue;

    assert(!OuterDivLoop.contains(UserBlock) &&
           "irreducible control flow detected");

    // phi nodes at the fringes of the dominance region
    if (!DT.dominates(&LoopHeader, UserBlock)) {
      // all PHI nodes of UserBlock become divergent
      for (auto &Phi : UserBlock->phis()) {
        analyzeTemporalSymbolic(Phi, OuterDivLoop);
      }
      continue;
    }

    // Taint outside users of values carried by OuterDivLoop.
    for (auto &I : *UserBlock) {
      analyzeTemporalSymbolic(I, OuterDivLoop);
    }

    // visit all blocks in the dominance region
    for (auto *SuccBlock : successors(UserBlock)) {
      if (!Visited.insert(SuccBlock).second) {
        continue;
      }
      TaintStack.push_back(SuccBlock);
    }
  } while (!TaintStack.empty());
}

void SymbolicVariableAnalysisImpl::propagateLoopExitSymbolic(
    const BasicBlock &DivExit, const Loop &InnerDivLoop) {
  LLVM_DEBUG(dbgs() << "\tpropLoopExitDiv " << DivExit.getName() << "\n");

  // Find outer-most loop that does not contain \p DivExit
  const Loop *DivLoop = &InnerDivLoop;
  const Loop *OuterDivLoop = DivLoop;
  const Loop *ExitLevelLoop = LI.getLoopFor(&DivExit);
  const unsigned LoopExitDepth =
      ExitLevelLoop ? ExitLevelLoop->getLoopDepth() : 0;
  while (DivLoop && DivLoop->getLoopDepth() > LoopExitDepth) {
    SymbolicLoops.insert(DivLoop); // all crossed loops are divergent
    OuterDivLoop = DivLoop;
    DivLoop = DivLoop->getParentLoop();
  }
  LLVM_DEBUG(dbgs() << "\tOuter-most left loop: " << OuterDivLoop->getName()
                    << "\n");

  analyzeLoopExitSymbolic(DivExit, *OuterDivLoop);
}

// this is a divergent join point - mark all phi nodes as divergent and push
// them onto the stack.
void SymbolicVariableAnalysisImpl::taintAndPushPhiNodes(
    const BasicBlock &JoinBlock) {
  LLVM_DEBUG(dbgs() << "taintAndPushPhiNodes in " << JoinBlock.getName()
                    << "\n");

  // ignore divergence outside the region
  if (!inRegion(JoinBlock)) {
    return;
  }

  // push non-divergent phi nodes in JoinBlock to the worklist
  for (const auto &Phi : JoinBlock.phis()) {
    if (isSymbolic(Phi))
      continue;
    // FIXME Theoretically ,the 'undef' value could be replaced by any other
    // value causing spurious divergence.
    if (Phi.hasConstantOrUndefValue())
      continue;
    if (markSymbolic(Phi))
      Worklist.push_back(&Phi);
  }
}

void SymbolicVariableAnalysisImpl::analyzeControlSymbolic(
    const Instruction &Term) {
  LLVM_DEBUG(dbgs() << "analyzeControlDiv " << Term.getParent()->getName()
                    << "\n");

  // Don't propagate divergence from unreachable blocks.
  if (!DT.isReachableFromEntry(Term.getParent()))
    return;

  const auto *BranchLoop = LI.getLoopFor(Term.getParent());

  const auto &DivDesc = SDA.getJoinBlocks(Term);

  // Iterate over all blocks now reachable by a disjoint path join
  for (const auto *JoinBlock : DivDesc.JoinDivBlocks) {
    taintAndPushPhiNodes(*JoinBlock);
  }

  assert(DivDesc.LoopDivBlocks.empty() || BranchLoop);
  for (const auto *DivExitBlock : DivDesc.LoopDivBlocks) {
    propagateLoopExitSymbolic(*DivExitBlock, *BranchLoop);
  }
}

void SymbolicVariableAnalysisImpl::compute() {
  // Initialize worklist.
  auto DivValuesCopy = SymbolicValues;
  for (const auto *DivVal : DivValuesCopy) {
    assert(isSymbolic(*DivVal) && "Worklist invariant violated!");
    pushUsers(*DivVal);
  }

  // All values on the Worklist are divergent.
  // Their users may not have been updated yed.
  while (!Worklist.empty()) {
    const Instruction &I = *Worklist.back();
    Worklist.pop_back();

    // propagate value divergence to users
    assert(isSymbolic(I) && "Worklist invariant violated!");
    pushUsers(I);
  }
}

bool SymbolicVariableAnalysisImpl::isAlwaysUniform(const Value &V) const {
  return UniformOverrides.contains(&V);
}

bool SymbolicVariableAnalysisImpl::isSymbolic(const Value &V) const {
  return SymbolicValues.contains(&V);
}

bool SymbolicVariableAnalysisImpl::isSymbolicUse(const Use &U) const {
  Value &V = *U.get();
  Instruction &I = *cast<Instruction>(U.getUser());
  return isSymbolic(V) || isTemporalSymbolic(*I.getParent(), V);
}

SymbolicVariableInfo::SymbolicVariableInfo(const Function &F,
                                           const DominatorTree &DT,
                                           const PostDominatorTree &PDT,
                                           const LoopInfo &LI,
                                           bool KnownReducible)
    : F(F), ContainsIrreducible(false) {
  if (!KnownReducible) {
    using RPOTraversal = ReversePostOrderTraversal<const Function *>;
    RPOTraversal FuncRPOT(&F);
    if (containsIrreducibleCFG<const BasicBlock *, const RPOTraversal,
                               const LoopInfo>(FuncRPOT, LI)) {
      ContainsIrreducible = true;
      return;
    }
  }
  SDA = std::make_unique<SyncDependenceAnalysis>(DT, PDT, LI);
  DA = std::make_unique<SymbolicVariableAnalysisImpl>(F, nullptr, DT, LI, *SDA,
                                                      /* LCSSA */ false);
}

void SymbolicVariableInfo::compute(const SymbolicSourcesInfo &SSI) {
  // if the function contains irreducible CFG, we cannot compute the analysis
  if (ContainsIrreducible) {
    return;
  }

  for (auto &I : instructions(F)) {
    if (SSI.isSymbolicSource(&I)) {
      DA->markSymbolic(I);
    }
  }

  for (auto &Arg : F.args()) {
    if (SSI.isSymbolicSource(&Arg)) {
      DA->markSymbolic(Arg);
    }
  }

  DA->compute();
}

SymbolicSourcesInfo::SymbolicSourcesInfo(Function &F, AAResults &AA,
                                         bool MarkAllLoadsSymbolic)
    : F(&F), AA(AA) {
  // find all symbolic sources

  // in main function, all arguments are symbolic
  if (F.getName() == "main") {
    for (const Argument &Arg : F.args()) {
      SymbolicSources.insert(&Arg);
    }
  }

  for (const Instruction &I : instructions(F)) {
    if (const CallInst *CI = dyn_cast<CallInst>(&I)) {

      // ignore indirect calls or calls to inline assembly
      if (CI->isIndirectCall() || CI->isInlineAsm()) {
        continue;
      }

      Function *CalledFunc = CI->getCalledFunction();

      // only process klee_make_symbolic
      if (!CalledFunc)
        continue;
      if (!CalledFunc->getName().contains("klee_make_symbolic"))
        continue;

      // klee_make_symbolic function creates a symbolic variable
      const Value *VoidPtrArg = CI->getOperand(0);

      // mark the pointer argument as symbolic
      markSymbolicSource(VoidPtrArg);
    }
  }

  // if MarkAllLoadsSymbolic is set, mark all loads as symbolic
  if (MarkAllLoadsSymbolic) {
    DEBUG("Marking all loads as symbolic sources in function " + F.getName().str() + "\n");
    for (const Instruction &I : instructions(F)) {
      if (const LoadInst *LI = dyn_cast<LoadInst>(&I)) {
        markSymbolicSource(LI);
      }
    }
  }

  // if this is a vararg function, find the struct.__va_list_tag struct type
  if (F.isVarArg()) {
    for (StructType *StructTy : F.getParent()->getIdentifiedStructTypes()) {
      if (StructTy->getName().startswith("struct.__va_list_tag")) {
        VaListTy = StructTy;
        break;
      }
    }
    assert(VaListTy && "Cannot find struct.__va_list_tag in module!");
  }
}

bool SymbolicSourcesInfo::markSymbolicVarargFunc() {
  // find the struct type of va_list_tag and find any alloca instruction that
  // use this type as its element type. Mark them as symbolic.
  AllocaInst *VaListAlloca = nullptr;
  for (Instruction &I : instructions(*F)) {
    if (AllocaInst *AI = dyn_cast<AllocaInst>(&I)) {
      if (AI->getAllocatedType()->isArrayTy() &&
          AI->getAllocatedType()->getArrayElementType() == VaListTy) {
        VaListAlloca = AI;
        break;
      }
    }
  }
  assert(VaListAlloca &&
         "Cannot find va_list alloca instruction in vararg function!");

  return markSymbolicSource(VaListAlloca);
}

bool SymbolicSourcesInfo::markSymbolicSource(const Value *Source) {
  if (!SymbolicSources.insert(Source).second)
    return false;
  // mark any instruction that alias with this source as symbolic
  for (const Instruction &I : instructions(*F)) {
    if (Source == &I)
      continue;
    auto Result = AA.alias(Source, &I);
    if (Result == AliasResult::MayAlias || Result == AliasResult::MustAlias) {
      SymbolicSources.insert(&I);
    }
  }
  // add the source to the symbolic sources
  SymbolicSources.insert(Source);
  return true;
}

ModuleSymbolicVariableAnalysis::ModuleSymbolicVariableAnalysis(
    Module &M, FunctionAnalysisManager &FAM, DenseSet<Function *> &DontAnalyze,
    bool MarkLoadsSymbolic)
    : M(M) {

  // alias analysis result
  auto GetAAResult = [&FAM](Function *F) -> AAResults & {
    return FAM.getResult<AAManager>(*F);
  };

  // dominator tree result
  auto GetDominatorTreeResult = [&FAM](Function *F) -> DominatorTree & {
    return FAM.getResult<DominatorTreeAnalysis>(*F);
  };
  // post dominator tree result
  auto GetPostDominatorTreeResult = [&FAM](Function *F) -> PostDominatorTree & {
    return FAM.getResult<PostDominatorTreeAnalysis>(*F);
  };
  // loop info result
  auto GetLoopInfoResult = [&FAM](Function *F) -> LoopInfo & {
    return FAM.getResult<LoopAnalysis>(*F);
  };

  // only analyze functions that are not marked as dont analyze
  for (Function &F : M) {
    if (F.isDeclaration())
      continue;
    if (DontAnalyze.count(&F))
      continue;
    FuncsToAnalyze.insert(&F);
  }

  //  create the analysis objects for each function
  for (Function *F : FuncsToAnalyze) {
    DominatorTree &DT = GetDominatorTreeResult(F);
    PostDominatorTree &PDT = GetPostDominatorTreeResult(F);
    LoopInfo &LI = GetLoopInfoResult(F);
    ModuleSymbolicInfo[F] = std::make_unique<SymbolicVariableInfo>(
        *F, DT, PDT, LI, /* KnownReducible */ false);
    AAResults &AA = GetAAResult(F);
    ModuleSymbolicSourcesInfo[F] =
        std::make_unique<SymbolicSourcesInfo>(*F, AA, MarkLoadsSymbolic);
    FunctionWorklist.insert(F);
  }

  while (!FunctionWorklist.empty()) {
    // process one function in the worklist
    const Function *F = *FunctionWorklist.begin();
    FunctionWorklist.erase(F);
    ModuleSymbolicInfo[F]->compute(*ModuleSymbolicSourcesInfo[F]);

    for (const Instruction &I : instructions(F)) {
      if (!isSymbolic(I))
        continue;
      // find symbolic call instructions
      if (const CallInst *CI = dyn_cast<CallInst>(&I)) {
        if (CI->isIndirectCall() || CI->isInlineAsm()) {
          continue;
        }
        Function *CalledFunc = CI->getCalledFunction();

        // if the function is not in the module, we cannot process it
        if (ModuleSymbolicSourcesInfo.count(CalledFunc) == 0)
          continue;

        // get symbolic source info
        auto &SymbolicSourceInfo = ModuleSymbolicSourcesInfo[CalledFunc];

        bool ProcessAgain = false;
        for (unsigned Idx = 0; Idx < CI->getNumArgOperands(); Idx++) {
          const Value *Arg = CI->getArgOperand(Idx);

          // constant arguments are not symbolic
          if (isa<Constant>(Arg))
            continue;

          // if this argument is not symbolic, ignore
          if (!isSymbolic(*Arg))
            continue;

          // if the argument is a vararg, then we need to re-process the
          // function if it is not marked as symbolic vararg function before
          if (Idx >= CalledFunc->arg_size()) {
            if (SymbolicSourceInfo->markSymbolicVarargFunc()) {
              ProcessAgain = true;
            }
            continue;
          }

          // if this argument is not discovered as symbolic source before, then
          // we need to re-process the function
          if (SymbolicSourceInfo->markSymbolicSource(CalledFunc->getArg(Idx))) {
            ProcessAgain = true;
          }
        }

        // re-process again if needed (must be in the FuncsTOAnalyze set)
        if (ProcessAgain && FunctionWorklist.count(CalledFunc) == 0 &&
            FuncsToAnalyze.count(CalledFunc) != 0) {
          FunctionWorklist.insert(CalledFunc);
        }
      }
      // FIXME : should we mark all values that alias with symblic store as symbolic?
      // process store instructions that store symbolic values
      // else if (const StoreInst *SI = dyn_cast<StoreInst>(&I)) {
      //   const Value *StoreValue = SI->getValueOperand();
      //   const Value *StorePointer = SI->getPointerOperand();
      //   if (isSymbolic(*StoreValue)) {
      //     // if the store instruction is not marked as symbolic source before,
      //     // then we need to re-process the function
      //     if (ModuleSymbolicSourcesInfo[F]->markSymbolicSource(StorePointer))
      //       FunctionWorklist.insert(F);
      //   }
      // }
    }
  }
}

bool ModuleSymbolicVariableAnalysis::isSymbolic(const Value &V) {

  if (const Argument *Arg = dyn_cast<Argument>(&V)) {
    return ModuleSymbolicInfo[Arg->getParent()]->isSymbolic(V);
  }

  if (const Instruction *I = dyn_cast<Instruction>(&V)) {
    return ModuleSymbolicInfo[I->getFunction()]->isSymbolic(V);
  }

  if (const Constant *C = dyn_cast<Constant>(&V)) {
    return false;
  }

  assert(false &&
         "Value is not an argument or instruction, this case not handled!");

  return false;
}

void ModuleSymbolicVariableAnalysis::print(raw_fd_ostream &OS) {
  for (const Function *F : FuncsToAnalyze) {
    if (F->isDeclaration())
      continue;
    OS << "Symbolic Variable Analysis for function : " << F->getName() << "\n";
    OS << "Arguments : \n";
    for (const Argument &Arg : F->args()) {
      OS << "  ";
      Arg.print(OS);
      OS << " : ";
      OS << (isSymbolic(Arg) ? "SYMBOLIC " : "CONCRETE") << "\n";
    }
    OS << "Instructions : \n";
    for (const BasicBlock &BB : *F) {
      OS << "Block : " << BB.getNameOrAsOperand() << ":\n";
      for (const Instruction &I : BB) {
        OS << "  ";
        I.print(OS);
        OS << " : ";
        OS << (isSymbolic(I) ? "SYMBOLIC " : "CONCRETE") << "\n";
      }
    }
  }
}

void ModuleSymbolicVariableAnalysis::printForFunction(
    raw_fd_ostream &OS, const std::string &FuncName) {
  SmallVector<const Function *> FuncsWithName;
  for (const Function *F : FuncsToAnalyze) {
    if (F->getName().contains(FuncName)) {
      FuncsWithName.push_back(F);
    }
  }
  for (const Function *F : FuncsWithName) {
    if (F->isDeclaration())
      continue;
    OS << "Symbolic Variable Analysis for function : " << F->getName() << "\n";
    OS << "Arguments : \n";
    for (const Argument &Arg : F->args()) {
      OS << "  ";
      Arg.print(OS);
      OS << " : ";
      OS << (isSymbolic(Arg) ? "SYMBOLIC " : "CONCRETE") << "\n";
    }
    OS << "Instructions : \n";
    for (const BasicBlock &BB : *F) {
      OS << "Block : " << BB.getNameOrAsOperand() << ":\n";
      for (const Instruction &I : BB) {
        OS << "  ";
        I.print(OS);
        OS << " : ";
        OS << (isSymbolic(I) ? "SYMBOLIC " : "CONCRETE") << "\n";
      }
    }
  }
}

// AnalysisKey SymbolicVariableAnalysis::Key;

// SymbolicVariableAnalysis::Result
// SymbolicVariableAnalysis::run(Function &F, FunctionAnalysisManager &AM) {
//   auto &DT = AM.getResult<DominatorTreeAnalysis>(F);
//   auto &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);
//   auto &LI = AM.getResult<LoopAnalysis>(F);
//   auto &TTI = AM.getResult<TargetIRAnalysis>(F);

//   return SymbolicVariableInfo(F, DT, PDT, LI, TTI, /* KnownReducible = */
//   false);
// }

// PreservedAnalyses
// DivergenceAnalysisPrinterPass::run(Function &F, FunctionAnalysisManager &FAM)
// {
//   auto &DI = FAM.getResult<DivergenceAnalysis>(F);
//   OS << "'Divergence Analysis' for function '" << F.getName() << "':\n";
//   if (DI.hasDivergence()) {
//     for (auto &Arg : F.args()) {
//       OS << (DI.isSymbolic(Arg) ? "DIVERGENT: " : "           ");
//       OS << Arg << "\n";
//     }
//     for (const BasicBlock &BB : F) {
//       OS << "\n           " << BB.getName() << ":\n";
//       for (auto &I : BB.instructionsWithoutDebug()) {
//         OS << (DI.isSymbolic(I) ? "DIVERGENT:     " : "               ");
//         OS << I << "\n";
//       }
//     }
//   }
//   return PreservedAnalyses::all();
// }
