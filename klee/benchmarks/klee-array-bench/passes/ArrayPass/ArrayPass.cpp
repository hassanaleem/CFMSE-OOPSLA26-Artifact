#include "llvm/Pass.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/PassRegistry.h"
#include "llvm/DebugInfo.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace SRG {
  /* 
   * Analyzes the code to print all global arrays (-print_arrays). The
   * output of the pass is in CSV format (separated by ';'):
   *
   * 1) U (uninitialized) / I (initialized)
   * 2) N (not constant)  / C (constant)
   * 3) name
   * 4) type
   * 5) filename:line (where the array is defined)
   *
   * Examples:
   *    U;N;message;[3 x i8]*;../../src/who.c:245
   *    I;C;version_etc_copyright;[47 x i8]*;../../lib/version-etc-fsf.c:26
   *
   */
  struct ArrayPass : public ModulePass {
    static char ID;

    ArrayPass() : ModulePass(ID) {}
    
    virtual bool runOnModule(Module &M) {
      DebugInfoFinder Finder;
      Finder.processModule(M);
      // iterates over global variables through their debugging information
      for (DebugInfoFinder::iterator DIFI = Finder.global_variable_begin(), DIFE = Finder.global_variable_end();
	   DIFI != DIFE;
	   DIFI++) {
	// get the debug information for global variables
	DIGlobalVariable GV(*DIFI);
	
	if (!GV.isGlobalVariable() || !GV.getGlobal()) {
	  // if it's not a global or constant, we skip
	  continue;
	}

	GlobalVariable *g = GV.getGlobal();

	bool of_interest = false;
	if (g->hasInitializer()) {
	  Constant *init = g->getInitializer();
	  if(isa<ArrayType>(init->getType())) {
	    of_interest = true;
	    if (isa<ConstantAggregateZero>(init)) {
	      errs() << "U;";
	    } else {
	      errs() << "I;";
	    }
	  }
	}
	
	if (of_interest) {
	  if (g->isConstant()) {
	    errs() << "C;";
	  } else {
	    errs() << "N;";
	  }
	  errs() << GV.getName() << ";";
	  g->getType()->print(errs());
	  errs() << ";" << GV.getFilename() << ":" << GV.getLineNumber() << '\n';
	}
      }
      
      return false; // does not modify code
    }

    void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
  };
}

char SRG::ArrayPass::ID = 0;
// Register the pass to work with OPT
static RegisterPass<SRG::ArrayPass> X("print_arrays", "Array Print Pass");

// Register pass with the Pass registry so it can be used directly as
// a clang plugin and run during compilation
static void registerArrayPass(const PassManagerBuilder &PMB, PassManagerBase &PM) {
  PM.add(new SRG::ArrayPass());
}
static RegisterStandardPasses Y(PassManagerBuilder::EP_EnabledOnOptLevel0, registerArrayPass);
static RegisterStandardPasses Z(PassManagerBuilder::EP_ModuleOptimizerEarly, registerArrayPass);
