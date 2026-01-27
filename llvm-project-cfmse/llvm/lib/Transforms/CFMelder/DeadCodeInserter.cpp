#include "DeadCodeInserter.h"
#include "CFMelderUtils.h"
#include "SeqAlignmentUtils.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Alignment.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InstructionCost.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <cstddef>
#include <memory>

#define ENABLE_UNSAFE_ARITH

cl::opt<bool> EnableUnsafeDCI("cfmse-unsafe-dci", cl::init(true),
                              cl::desc("Insert unsafe loads/stores in DCI"));

DeadCodeInserter::DeadCodeInserter(Function *F, AlignedSeq<Value *> &Alignment,
                                   DominatorTree &DT)
    : F(F), AlignResultRef(Alignment), DT(DT) {
  // find the DCI global variable
  auto GVItBegin = F->getParent()->global_begin();
  auto GVItEnd = F->getParent()->global_end();
  auto Found = std::find_if(GVItBegin, GVItEnd, [](GlobalVariable &GV) {
    return GV.getName() == "cfmse.dci_gv";
  });

  assert(Found != GVItEnd && "DCI global variable not found!");
  DCIGV = &*Found;

  // update DCIGEP and DCIGVCastingMap
  for (Instruction &I : F->getEntryBlock()) {
    if (auto *GEP = dyn_cast<GetElementPtrInst>(&I)) {
      if (GEP->getPointerOperand() == DCIGV) {
        DCIGEP = GEP;
      }
    } else if (auto *Cast = dyn_cast<BitCastInst>(&I)) {
      if (Cast->getOperand(0) == DCIGV) {
        DCIGVCastingMap[Cast->getType()] = Cast;
      }
    }
  }
  assert(DCIGEP != nullptr && "DCI GEP not found!");
}

Instruction *DeadCodeInserter::insertClone(Instruction *I,
                                           AlignedPair<Value *> &PrevInstPair) {
  // find insert point
  BasicBlock *ParentBlock = I->getParent();
  bool DCToLeft = !(VMapLToR.count(ParentBlock));
  BasicBlock *DCBlock = DCToLeft ? dyn_cast<BasicBlock>(VMapRToL[ParentBlock])
                                 : dyn_cast<BasicBlock>(VMapLToR[ParentBlock]);
  Instruction *InsertBefore = &*DCBlock->getFirstInsertionPt();

  if (PrevInstPair.getLeft() != nullptr) {
    Instruction *InsertAfter =
        DCToLeft ? dyn_cast<Instruction>(PrevInstPair.getLeft())
                 : dyn_cast<Instruction>(PrevInstPair.getRight());
    InsertBefore = InsertAfter->getNextNode();
  }

  // clone and insert the dc instruction
  Instruction *NewI = I->clone();

  // update the mergedLineNum metadata, since this is DEAD instruction we give
  // -2 as the line number
  // TODO : this is a hack
  if (auto *MD = I->getMetadata("mergedLineNum")) {
    LLVMContext &Context = ParentBlock->getParent()->getContext();
    MDNode *MergedLineNode =
        MDNode::get(Context, MDString::get(Context, std::to_string(-2)));
    I->setMetadata("mergedLineNum", MergedLineNode);
  }

  IRBuilder<> Builder(DCBlock->getParent()->getContext());
  Builder.SetInsertPoint(InsertBefore);
  Builder.Insert(NewI);
  return NewI;
}

void DeadCodeInserter::setDCOperand(Instruction *DC, Value *Op,
                                    unsigned OpIdx) {
  if (Op && !DT.dominates(Op, DC)) {
    // find the corresponding instruction for this operand
    Value *CorrDC = VMapLToR.count(Op) ? VMapLToR[Op] : VMapRToL[Op];
    assert(CorrDC && "Corresponding dead code operand not found!");
    DC->setOperand(OpIdx, CorrDC);
  }
}

void DeadCodeInserter::setOperandsForUnaryInst(Instruction *I,
                                               Instruction *DC) {
  Instruction *Op = dyn_cast<Instruction>(DC->getOperand(0));
  setDCOperand(DC, Op, 0);
}

void DeadCodeInserter::setOperandsForBinaryInst(Instruction *I,
                                                Instruction *DC) {
  Instruction *Op0 = dyn_cast<Instruction>(DC->getOperand(0));
  Instruction *Op1 = dyn_cast<Instruction>(DC->getOperand(1));

  setDCOperand(DC, Op0, 0);
  setDCOperand(DC, Op1, 1);
}

void DeadCodeInserter::sanitizeAddOp(Instruction *Add, Instruction *DC) {
  // try to minimize select ops
  setOperandsForBinaryInst(Add, DC);

#ifndef ENABLE_UNSAFE_ARITH
  // set second operand to 0 to make sure we don't have any overflow
  Constant *Zero = DC->getType()->isIntegerTy()
                       ? ConstantInt::get(DC->getType(), 0)
                       : ConstantFP::get(DC->getType(), 0.0);

  DC->setOperand(1, Zero);
#endif
}

void DeadCodeInserter::sanitizeSubOp(Instruction *Sub, Instruction *DC) {
  // need to be hadled same as add
  sanitizeAddOp(Sub, DC);
}

void DeadCodeInserter::sanitizeMulOp(Instruction *Mul, Instruction *DC) {
  // try to minimize select ops
  setOperandsForBinaryInst(Mul, DC);
#ifndef ENABLE_UNSAFE_ARITH
  // set second operand to 1 to make sure we don't have any overflow
  Constant *One = DC->getType()->isIntegerTy()
                      ? ConstantInt::get(DC->getType(), 1)
                      : ConstantFP::get(DC->getType(), 1.0);
  DC->setOperand(1, One);
#endif
}

void DeadCodeInserter::sanitizeDivOp(Instruction *Div, Instruction *DC) {
  // try to minimize select ops
  setOperandsForBinaryInst(Div, DC);
  // set second operand to 1 to make sure we don't have dvision by zero
  Constant *One = DC->getType()->isIntegerTy()
                      ? ConstantInt::get(DC->getType(), 1)
                      : ConstantFP::get(DC->getType(), 1.0);
  DC->setOperand(1, One);
}

void DeadCodeInserter::sanitizeSRemOp(Instruction *Rem, Instruction *DC) {
  // try to minimize select ops
  setOperandsForBinaryInst(Rem, DC);
  // set second operand to 1 for remainder
  Constant *One = DC->getType()->isIntegerTy()
                      ? ConstantInt::get(DC->getType(), 1)
                      : ConstantFP::get(DC->getType(), 1.0);
  DC->setOperand(1, One);
}

void DeadCodeInserter::sanitizeURemOp(Instruction *Rem, Instruction *DC) {
  // try to minimize select ops
  setOperandsForBinaryInst(Rem, DC);
  // set second operand to 1 for remainder
  Constant *One = DC->getType()->isIntegerTy()
                      ? ConstantInt::get(DC->getType(), 1)
                      : ConstantFP::get(DC->getType(), 1.0);
  DC->setOperand(1, One);
}

void DeadCodeInserter::sanitizeGEP(Instruction *GEP, Instruction *DC) {
  // set all operands to corresponding dead code operands
  for (unsigned I = 0; I < GEP->getNumOperands(); I++) {
    setDCOperand(DC, GEP->getOperand(I), I);
  }
}

void DeadCodeInserter::sanitizeLoad(Instruction *Load, Instruction *DC) {
  Function *F = Load->getParent()->getParent();
  Module *M = F->getParent();
  LLVMContext &Context = M->getContext();
  BasicBlock *Entry = &F->getEntryBlock();

  LoadInst *OrigLoad = dyn_cast<LoadInst>(Load);
  LoadInst *DCILoad = dyn_cast<LoadInst>(DC);
  Type *PtrOPType = OrigLoad->getPointerOperandType();

  // if it is loading a byte, we can just use the GEP
  if (PtrOPType == Type::getInt8Ty(Context)) {
    DCILoad->setOperand(0, DCIGEP);
    return;
  }

  // if the cast is inside the CastingMap, we can use it
  if (DCIGVCastingMap.count(PtrOPType)) {
    DCILoad->setOperand(0, DCIGVCastingMap[PtrOPType]);
    return;
  }

  // else create a cast to i8* in the entry block and load from there
  Value *Cast = BitCastInst::Create(Instruction::BitCast, DCIGEP, PtrOPType,
                                    "dci_cast", Entry->getTerminator());
  DCILoad->setOperand(0, Cast);

  // add the cast to the map
  DCIGVCastingMap[PtrOPType] = Cast;
}

void DeadCodeInserter::sanitizeStore(Instruction *Store, Instruction *DC) {
  StoreInst *OrigStore = dyn_cast<StoreInst>(Store);
  StoreInst *DCIStore = dyn_cast<StoreInst>(DC);

  // set the value operand to zero in DCIStore
  DCIStore->setOperand(
      0, ConstantInt::get(OrigStore->getValueOperand()->getType(), 0));

  Type *PtrOPType = OrigStore->getPointerOperandType();
  // check if this type is already in the map
  if (DCIGVCastingMap.count(PtrOPType)) {
    DCIStore->setOperand(1, DCIGVCastingMap[PtrOPType]);
    return;
  }

  // otherwise create a cast from i8* to PtrOPType at the end of the entry block
  Value *Cast =
      BitCastInst::Create(Instruction::BitCast, DCIGEP, PtrOPType, "dci_cast",
                          F->getEntryBlock().getTerminator());
  DCIStore->setOperand(1, Cast);
  // add the cast to the map
  DCIGVCastingMap[PtrOPType] = Cast;
}

static AlignedPair<Value *>
convertToDeadStore(Instruction *Store, Instruction *DC, bool OrigIsLeft) {
  StoreInst *OrigStore = dyn_cast<StoreInst>(Store);
  StoreInst *DCIStore = dyn_cast<StoreInst>(DC);

  Value *OrigPtr = OrigStore->getPointerOperand();
  Value *DCPtr = DCIStore->getPointerOperand();
  Type *LoadType = OrigStore->getValueOperand()->getType();
  // create a load from DCPtr and insert it before DCIStore
  IRBuilder<> Builder(DCIStore);
  LoadInst *ValueAtPtr = Builder.CreateLoad(LoadType, DCPtr, "dci_dummy_load");
  DCIStore->setOperand(0, ValueAtPtr);

  // set debug loc for the dead load
  if (DCIStore->getDebugLoc())
    ValueAtPtr->setDebugLoc(DCIStore->getDebugLoc());

  // insert the same load before the original store
  Builder.SetInsertPoint(Store);
  LoadInst *DummyLoad =
      Builder.CreateLoad(LoadType, OrigPtr, "orig_dummy_load");

  // set debug loc for the dummy load
  if (Store->getDebugLoc())
    DummyLoad->setDebugLoc(Store->getDebugLoc());

  AlignedPair<Value *> LoadPair(OrigIsLeft ? DummyLoad : ValueAtPtr,
                                OrigIsLeft ? ValueAtPtr : DummyLoad);
  return LoadPair;
}

void DeadCodeInserter::sanitizeSExt(Instruction *SExt, Instruction *DC) {
  setOperandsForUnaryInst(SExt, DC);
}

void DeadCodeInserter::sanitizeZExt(Instruction *ZExt, Instruction *DC) {
  setOperandsForUnaryInst(ZExt, DC);
}

void DeadCodeInserter::sanitizeTrunc(Instruction *Trunc, Instruction *DC) {
  setOperandsForUnaryInst(Trunc, DC);
}

void DeadCodeInserter::sanitizeBitCast(Instruction *BitCast, Instruction *DC) {
  setOperandsForUnaryInst(BitCast, DC);
}

void DeadCodeInserter::sanitizePtrToInt(Instruction *PtrToInt,
                                        Instruction *DC) {
  setOperandsForUnaryInst(PtrToInt, DC);
}

void DeadCodeInserter::sanitizeSIToFP(Instruction *SIToFP, Instruction *DC) {
  setOperandsForUnaryInst(SIToFP, DC);
}

void DeadCodeInserter::sanitizeUIToFP(Instruction *UIToFP, Instruction *DC) {
  setOperandsForUnaryInst(UIToFP, DC);
}

void DeadCodeInserter::sanitizeFPToUI(Instruction *FPToUI, Instruction *DC) {
  setOperandsForUnaryInst(FPToUI, DC);
}

void DeadCodeInserter::sanitizeFNeg(Instruction *FNeg, Instruction *DC) {
  setOperandsForUnaryInst(FNeg, DC);
}

void DeadCodeInserter::sanitizeFPTrunc(Instruction *FPTrunc, Instruction *DC) {
  setOperandsForUnaryInst(FPTrunc, DC);
}

void DeadCodeInserter::sanitizeFPExt(Instruction *FPExt, Instruction *DC) {
  setOperandsForUnaryInst(FPExt, DC);
}

void DeadCodeInserter::sanitizeICmp(Instruction *ICmp, Instruction *DC) {
  setOperandsForBinaryInst(ICmp, DC);
}

void DeadCodeInserter::sanitizeFCmp(Instruction *FCmp, Instruction *DC) {
  setOperandsForBinaryInst(FCmp, DC);
}

void DeadCodeInserter::sanitizeSelect(Instruction *Select, Instruction *DC) {
  Instruction *Op0 = dyn_cast<Instruction>(DC->getOperand(0));
  Instruction *Op1 = dyn_cast<Instruction>(DC->getOperand(1));
  Instruction *Op2 = dyn_cast<Instruction>(DC->getOperand(2));
  setDCOperand(DC, Op0, 0);
  setDCOperand(DC, Op1, 1);
  setDCOperand(DC, Op2, 2);
}

void DeadCodeInserter::sanitizeShl(Instruction *Or, Instruction *DC) {
  setOperandsForBinaryInst(Or, DC);

#ifndef ENABLE_UNSAFE_ARITH
  // set second operand to 0 to make sure we don't have any overflow
  Constant *Zero = DC->getType()->isIntegerTy()
                       ? ConstantInt::get(DC->getType(), 0)
                       : ConstantFP::get(DC->getType(), 0.0);

  DC->setOperand(1, Zero);
#endif
}

void DeadCodeInserter::sanitizeLShr(Instruction *Or, Instruction *DC) {
  setOperandsForBinaryInst(Or, DC);

#ifndef ENABLE_UNSAFE_ARITH
  // set second operand to 0 to make sure we don't have any overflow
  Constant *Zero = DC->getType()->isIntegerTy()
                       ? ConstantInt::get(DC->getType(), 0)
                       : ConstantFP::get(DC->getType(), 0.0);

  DC->setOperand(1, Zero);
#endif
}
void DeadCodeInserter::sanitizeAShr(Instruction *Or, Instruction *DC) {
  setOperandsForBinaryInst(Or, DC);

#ifndef ENABLE_UNSAFE_ARITH
  // set second operand to 0 to make sure we don't have any overflow
  Constant *Zero = DC->getType()->isIntegerTy()
                       ? ConstantInt::get(DC->getType(), 0)
                       : ConstantFP::get(DC->getType(), 0.0);

  DC->setOperand(1, Zero);
#endif
}

void DeadCodeInserter::sanitizeAnd(Instruction *Or, Instruction *DC) {
  setOperandsForBinaryInst(Or, DC);
}

void DeadCodeInserter::sanitizeOr(Instruction *Or, Instruction *DC) {
  setOperandsForBinaryInst(Or, DC);
}

void DeadCodeInserter::sanitizeXor(Instruction *Or, Instruction *DC) {
  setOperandsForBinaryInst(Or, DC);
}

void DeadCodeInserter::run() {
  DEBUG("Running DCI!\n");

  // final alignment result after DCI
  AlignedSeq<Value *> FinalResult;
  // preprocessed alignment result (make loads and stores unaligned if loading
  // from different addresses)
  AlignedSeq<Value *> PreprocessedSeq;
  // keep track of the previous instruction pair
  AlignedPair<Value *> PrevInstPair(nullptr, nullptr);

  // this function checks if two GEPs are computing the same address
  auto ComputesSameAddress = [&](GetElementPtrInst *GEP1,
                                 GetElementPtrInst *GEP2) -> bool {
    if (GEP1->getNumOperands() != GEP2->getNumOperands())
      return false;
    for (unsigned I = 0; I < GEP1->getNumOperands(); I++) {
      if (GEP1->getOperand(I) != GEP2->getOperand(I))
        return false;
    }
    return true;
  };

  // this function,
  // 1. makes loads unaligned if they are loading from different addresses
  // 2. makes stores unaligned if they are storing to different addresses
  // 3. makes GEPs unaligned if they are computing different addresses
  auto PreprocessLoadStores = [&]() {
    for (auto &Pair : AlignResultRef) {

      // skip unaligned pairs
      if (Pair.missMatch()) {
        PreprocessedSeq.push_back(Pair);
        continue;
      }

      Value *L = Pair.getLeft();
      Value *R = Pair.getRight();

      // skip basic blocks
      if (isa<BasicBlock>(L)) {
        PreprocessedSeq.push_back(Pair);
        continue;
      }

      Instruction *LI = dyn_cast<Instruction>(L);
      switch (LI->getOpcode()) {
      // loads must be aligned if they are loading from different addresses
      case Instruction::Load: {
        LoadInst *LoadL = dyn_cast<LoadInst>(L);
        LoadInst *LoadR = dyn_cast<LoadInst>(R);
        if (LoadL->getPointerOperand() != LoadR->getPointerOperand()) {
          // make loads unaligned
          PreprocessedSeq.push_back(AlignedPair<Value *>(L, nullptr));
          PreprocessedSeq.push_back(AlignedPair<Value *>(nullptr, R));
        } else {
          PreprocessedSeq.push_back(Pair);
        }
        break;
      }
      // stores must be aligned if they are storing to different addresses
      case Instruction::Store: {
        StoreInst *StoreL = dyn_cast<StoreInst>(L);
        StoreInst *StoreR = dyn_cast<StoreInst>(R);
        if (StoreL->getPointerOperand() != StoreR->getPointerOperand()) {
          // make stores unaligned
          PreprocessedSeq.push_back(AlignedPair<Value *>(L, nullptr));
          PreprocessedSeq.push_back(AlignedPair<Value *>(nullptr, R));
        } else {
          PreprocessedSeq.push_back(Pair);
        }
        break;
      }
      // address computations must be unaligned
      case Instruction::GetElementPtr: {
        if (!ComputesSameAddress(dyn_cast<GetElementPtrInst>(L),
                                 dyn_cast<GetElementPtrInst>(R))) {
          PreprocessedSeq.push_back(AlignedPair<Value *>(L, nullptr));
          PreprocessedSeq.push_back(AlignedPair<Value *>(nullptr, R));
        } else {
          PreprocessedSeq.push_back(Pair);
        }
        break;
      }
      default: {
        PreprocessedSeq.push_back(Pair);
      }
      }
    }
  };

  // make loads and stores unaligned if loading from different addresses
  // this only works in unsafe mode
  if (EnableUnsafeDCI)
    PreprocessLoadStores();

  for (AlignedPair<Value *> &Pair : PreprocessedSeq) {
#ifdef DCI_DEBUG
    if (Pair.getLeft())
      Pair.getLeft()->print(errs());
    else
      errs() << "_";
    errs() << ":";
    if (Pair.getRight())
      Pair.getRight()->print(errs());
    else
      errs() << "_";
    errs() << "\n";
#endif
    if (Pair.missMatch()) {
      bool IsLeft = Pair.getLeft() != nullptr;
      Instruction *UnalignedI = IsLeft ? dyn_cast<Instruction>(Pair.getLeft())
                                       : dyn_cast<Instruction>(Pair.getRight());

      Instruction *DCInst = insertClone(UnalignedI, PrevInstPair);

      switch (UnalignedI->getOpcode()) {
      case Instruction::Add:
      case Instruction::FAdd: {
        sanitizeAddOp(UnalignedI, DCInst);
        break;
      }
      case Instruction::Sub:
      case Instruction::FSub: {
        sanitizeSubOp(UnalignedI, DCInst);
        break;
      }
      case Instruction::Mul:
      case Instruction::FMul: {
        sanitizeMulOp(UnalignedI, DCInst);
        break;
      }
      case Instruction::SDiv:
      case Instruction::UDiv:
      case Instruction::FDiv: {
        sanitizeDivOp(UnalignedI, DCInst);
        break;
      }
      case Instruction::GetElementPtr: {
        sanitizeGEP(UnalignedI, DCInst);
        break;
      }
      case Instruction::Load: {
        // if unsage loads are allowed no need to sanitize
        // but make sure to load from the same address
        if (EnableUnsafeDCI) {
          setDCOperand(DCInst, DCInst->getOperand(0), 0);
          break;
        }
        sanitizeLoad(UnalignedI, DCInst);
        break;
      }
      case Instruction::Store: {
        if (EnableUnsafeDCI) {
          // make the store use the same value in the store address
          // i.e. it does not change the memory
          setDCOperand(DCInst, DCInst->getOperand(1), 1);
          auto NewLoadPair = convertToDeadStore(UnalignedI, DCInst, IsLeft);
          FinalResult.push_back(NewLoadPair);
          break;
        }
        sanitizeStore(UnalignedI, DCInst);
        break;
      }
      case Instruction::SExt: {
        sanitizeSExt(UnalignedI, DCInst);
        break;
      }
      case Instruction::ZExt: {
        sanitizeZExt(UnalignedI, DCInst);
        break;
      }
      case Instruction::Trunc: {
        sanitizeTrunc(UnalignedI, DCInst);
        break;
      }
      case Instruction::ICmp: {
        sanitizeICmp(UnalignedI, DCInst);
        break;
      }
      case Instruction::FCmp: {
        sanitizeFCmp(UnalignedI, DCInst);
        break;
      }
      case Instruction::Select: {
        sanitizeSelect(UnalignedI, DCInst);
        break;
      }
      case Instruction::Or: {
        sanitizeOr(UnalignedI, DCInst);
        break;
      }
      case Instruction::And: {
        sanitizeAnd(UnalignedI, DCInst);
        break;
      }
      case Instruction::Xor: {
        sanitizeXor(UnalignedI, DCInst);
        break;
      }
      case Instruction::Shl: {
        sanitizeShl(UnalignedI, DCInst);
        break;
      }
      case Instruction::LShr: {
        sanitizeLShr(UnalignedI, DCInst);
        break;
      }
      case Instruction::AShr: {
        sanitizeAShr(UnalignedI, DCInst);
        break;
      }
      case Instruction::BitCast: {
        sanitizeBitCast(UnalignedI, DCInst);
        break;
      }
      case Instruction::PtrToInt: {
        sanitizePtrToInt(UnalignedI, DCInst);
        break;
      }
      case Instruction::SIToFP: {
        sanitizeSIToFP(UnalignedI, DCInst);
        break;
      }
      case Instruction::UIToFP: {
        sanitizeUIToFP(UnalignedI, DCInst);
        break;
      }

      case Instruction::FPToUI: {
        sanitizeFPToUI(UnalignedI, DCInst);
        break;
      }

      case Instruction::FNeg: {
        sanitizeFNeg(UnalignedI, DCInst);
        break;
      }

      case Instruction::FPTrunc: {
        sanitizeFPTrunc(UnalignedI, DCInst);
        break;
      }

      case Instruction::FPExt: {
        sanitizeFPExt(UnalignedI, DCInst);
        break;
      }

      case Instruction::SRem: {
        sanitizeSRemOp(UnalignedI, DCInst);
        break;
      }
      case Instruction::URem: {
        sanitizeURemOp(UnalignedI, DCInst);
        break;
      }
      case Instruction::FRem:
      default:
        INFO("Unhandled instruction: ");
        UnalignedI->print(errs());
        errs() << "\n";
        assert(false && "Unsupported unaligned instruction!");
      }

      // update the alignment result
      if (IsLeft) {
        Pair.setRight(DCInst);
      } else {
        Pair.setLeft(DCInst);
      }
    }

    // update the mapping, we need this during DCI
    VMapLToR[Pair.getLeft()] = Pair.getRight();
    VMapRToL[Pair.getRight()] = Pair.getLeft();

    // reset prev pair at basic block boundries
    if (dyn_cast<BasicBlock>(Pair.getLeft()) != nullptr) {
      PrevInstPair.setLeft(nullptr);
      PrevInstPair.setRight(nullptr);
    } else {
      PrevInstPair.setLeft(Pair.getLeft());
      PrevInstPair.setRight(Pair.getRight());
    }
    FinalResult.push_back(Pair);
  }

  // clear and update the final result
  AlignResultRef.clear();
  AlignResultRef = FinalResult;

#ifdef DCI_DEBUG
  DEBUG << "Final alignment result after DCI: \n";
  for (auto &Entry : AlignResult) {
    if (Entry.getLeft())
      Entry.getLeft()->print(errs());
    else
      errs() << "_";
    errs() << ":";
    if (Entry.getRight())
      Entry.getRight()->print(errs());
    else
      errs() << "_";
    errs() << "\n";
  }
#endif
}