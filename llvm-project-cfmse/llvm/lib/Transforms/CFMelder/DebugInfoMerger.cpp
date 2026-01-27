#include "llvm/Transforms/CFMelder/DebugInfoMerger.h"
#include "CFMelderUtils.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Metadata.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
#include <sstream>
#include <string>

using namespace llvm;

void DebugInfoMerger::printMetadata(const Function &F) {
  for (auto &BB : make_range(F.begin(), F.end())) {
    // showing different way of accessing metadata
    for (auto &INST : make_range(BB.begin(), BB.end())) {
      if (MDNode *N = INST.getMetadata("mergedLineNum")) {
        INST.print(errs());
        errs() << " -> Merged Line Number is ";
        errs() << cast<MDString>(N->getOperand(0))->getString() << "\n";
      } else if (const DebugLoc &debugInfo = INST.getDebugLoc()) {
        INST.print(errs());
        errs() << " -> Regular Line Number is ";
        errs() << debugInfo.getLine() << "\n";
      } else {
        INST.print(errs());
        errs() << " -> No Line Number information!\n";
      }
    }
  }
}

void DebugInfoMerger::printMetadata(const Module &M) {
  for (auto &F : M) {
    if (F.isDeclaration()) {
      continue;
    }
    INFO("Printing metadata for function "  + F.getName().str() + "\n");
    printMetadata(F);
  }
}

void DebugInfoMerger::initializeMetadata(Module &M) {
  for (auto &F : M) {
    if (F.isDeclaration()) {
      continue;
    }
    initializeMetadata(F);
  }
}

void DebugInfoMerger::initializeMetadata(Function &F) {

  DEBUG("Initializing metadata for function " + F.getName().str() + "\n");
  LLVMContext &Context = F.getContext();

  // get the source filename of the function
  StringRef SourceFile = "";
  if (F.getSubprogram()) {
    SourceFile = F.getSubprogram()->getFilename();
  }

  for (auto &BB : F) {
    for (auto &I : BB) {
      // set source file name for this instruction
      MDNode *SourceFileNode =
          MDNode::get(Context, MDString::get(Context, SourceFile));
      I.setMetadata("sourceFile", SourceFileNode);

      const DebugLoc &IDebugLoc = I.getDebugLoc();
      // FIXME : if no line number is provided, we use -1
      int LineNo = -1;
      if (IDebugLoc)
        LineNo = IDebugLoc.getLine();

      MDNode *MergedLineNode =
          MDNode::get(Context, MDString::get(Context, std::to_string(LineNo)));
      I.setMetadata("mergedLineNum", MergedLineNode);
    }
  }
}

void DebugInfoMerger::updateMetaData(Instruction *LeftI, Instruction *RightI,
                                     Instruction *MergedI) {
  if (!(LeftI && RightI)) {
    return;
  }
  Function *F = LeftI->getParent()->getParent();
  LLVMContext &LlvmContext = F->getContext();

  MDNode *LeftMergedLineNode = LeftI->getMetadata("mergedLineNum");
  MDNode *RightMergedLineNode = RightI->getMetadata("mergedLineNum");

  if (!(LeftMergedLineNode && RightMergedLineNode)) {
    return;
  }

  // let's keep the line numbers in a set to avoid duplicates
  SmallSet<std::string, 8> LineSet;

  // collect all line numbers from left instruction
  for (unsigned I = 0, E = LeftMergedLineNode->getNumOperands(); I != E; ++I) {
    MDString *LineNo = dyn_cast<MDString>(LeftMergedLineNode->getOperand(I));
    if (LineNo) {
      LineSet.insert(LineNo->getString().str());
    }
  }
  // collect all line numbers from right instruction
  for (unsigned I = 0, E = RightMergedLineNode->getNumOperands(); I != E; ++I) {
    MDString *LineNo = dyn_cast<MDString>(RightMergedLineNode->getOperand(I));
    if (LineNo) {
      LineSet.insert(LineNo->getString().str());
    }
  }

  // create a string stream to store the merged line numbers
  std::stringstream SS;
  for (auto IB = LineSet.begin(), IE = LineSet.end(); IB != IE; ++IB) {
    SS << *IB;
    if (std::next(IB) != IE) {
      SS << ",";
    }
  }

  // set the merged line number metadata
  MDNode *MergedLineNode = MDNode::get(LlvmContext, MDString::get(LlvmContext, SS.str()));
  MergedI->setMetadata("mergedLineNum", MergedLineNode);

}