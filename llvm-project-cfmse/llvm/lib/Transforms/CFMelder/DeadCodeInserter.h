#ifndef LLVM_LIB_DEADCODE_INSERTER_H
#define LLVM_LIB_DEADCODE_INSERTER_H
#include "SeqAlignmentUtils.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Value.h"
#include <utility>

using namespace llvm;

// #define DCI_DEBUG

class DeadCodeInserter {
private:
  using ValueMap = DenseMap<Value *, Value *>;
  Function* F;
  AlignedSeq<Value *> &AlignResultRef;
  // corresponding values L to R map
  ValueMap VMapLToR;
  // corresponding values R to L map
  ValueMap VMapRToL;
  DominatorTree &DT;

  /// global variable for dead loads/stores to use
  GlobalVariable *DCIGV = nullptr;
  GetElementPtrInst *DCIGEP = nullptr;
  DenseMap<Type *, Value *> DCIGVCastingMap;

  ///  ---- utility functions to insert dead code ----
  /// clone the unaligned instruction and insert it at the oposite side
  Instruction *insertClone(Instruction *I, AlignedPair<Value *> &PrevInstPair);

  /// utility function to set operands for a dead code instruction
  void setDCOperand(Instruction *DC, Value *Op, unsigned OpIdx);

  ///  --- functions to set operands for the dead code instruction type ---
  /// arithmetic instructions
  void sanitizeAddOp(Instruction *Add, Instruction *DC);
  void sanitizeSubOp(Instruction *Sub, Instruction *DC);
  void sanitizeMulOp(Instruction *Mul, Instruction *DC);
  void sanitizeDivOp(Instruction *Div, Instruction *DC);
  void sanitizeSRemOp(Instruction *Rem, Instruction *DC);
  void sanitizeURemOp(Instruction *Rem, Instruction *DC);

  /// memory instructions
  void sanitizeGEP(Instruction *GEP, Instruction *DC);
  void sanitizeLoad(Instruction *Load, Instruction *DC);
  void sanitizeStore(Instruction *Store, Instruction *DC);

  /// conversion instructions
  void sanitizeSExt(Instruction *SExt, Instruction *DC);
  void sanitizeZExt(Instruction *ZExt, Instruction *DC);
  void sanitizeTrunc(Instruction *Trunc, Instruction *DC);
  void sanitizeBitCast(Instruction *BitCast, Instruction *DC);
  void sanitizePtrToInt(Instruction *PtrToInt, Instruction *DC);
  void sanitizeSIToFP(Instruction *SIToFP, Instruction *DC);
  void sanitizeUIToFP(Instruction *UIToFP, Instruction *DC);
  void sanitizeFPToUI(Instruction *FPToUI, Instruction *DC);
  void sanitizeFPTrunc(Instruction *FPTrunc, Instruction *DC);
  void sanitizeFPExt(Instruction *FPExt, Instruction *DC);


  /// Other instructions
  void sanitizeICmp(Instruction *ICmp, Instruction *DC);
  void sanitizeFCmp(Instruction *FCmp, Instruction *DC);
  void sanitizeSelect(Instruction* Select, Instruction* DC);

  /// Bitwise binary instructions
  void sanitizeShl(Instruction *Or, Instruction *DC);
  void sanitizeLShr(Instruction *Or, Instruction *DC);
  void sanitizeAShr(Instruction *Or, Instruction *DC);
  void sanitizeAnd(Instruction *Or, Instruction *DC);
  void sanitizeOr(Instruction *Or, Instruction *DC);
  void sanitizeXor(Instruction *Or, Instruction *DC);


  /// -- utility functions to insert dead code --
  void setOperandsForUnaryInst(Instruction *I, Instruction *DC);
  void setOperandsForBinaryInst(Instruction *I, Instruction *DC);

  /// -- floating point instructions --
  void sanitizeFNeg(Instruction *FNeg, Instruction *DC);
  

public:
  DeadCodeInserter(Function* F, AlignedSeq<Value *> &Alignment, DominatorTree &DT);

  void run();
};

#endif