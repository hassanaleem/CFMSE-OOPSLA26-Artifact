#ifndef LLVM_TRANSFORMS_CFMELDER_CFMSE_H
#define LLVM_TRANSFORMS_CFMELDER_CFMSE_H

#include "llvm/IR/Operator.h"
#include "llvm/IR/PassManager.h"
#include <unordered_set>

namespace llvm {

struct CFMSEOptions {
private:
  std::unordered_set<std::string> DontTouchFunctions;
  std::unordered_set<std::string> DontTouchLocs;

public:
  bool OnlyAnalysis = false;
  bool OnlyMergeDiamond = true;
  bool OnlySymbolicBranches = true;
  bool OnlyInLoops = true;
  bool MarkAllLoadsSymbolic = false;
  function_ref<bool(const std::string, const std::string)> IsExternFuncOrFile = nullptr;

  CFMSEOptions() = default;
  CFMSEOptions(
      bool OnlyAnalysis, bool OnlyMergeDiamond, bool OnlySymbolicBranches,
      bool OnlyInLoops, bool MarkAllLoadsSymbolic = true,
      function_ref<bool(const std::string, const std::string)> IsExternFuncOrFile = nullptr)
      : OnlyAnalysis(OnlyAnalysis), OnlyMergeDiamond(OnlyMergeDiamond),
        OnlySymbolicBranches(OnlySymbolicBranches), OnlyInLoops(OnlyInLoops),
        MarkAllLoadsSymbolic(MarkAllLoadsSymbolic),
        IsExternFuncOrFile(IsExternFuncOrFile) {}

  // filter out external functions (e.g. libc functions) from CFMSE
  bool isExternFuncOrFile(const std::string FuncName, const std::string FileName) {
    if (IsExternFuncOrFile)
      return IsExternFuncOrFile(FuncName, FileName);
    return false;
  }

  bool isDontTouchFunction(const std::string FuncName) {
    return DontTouchFunctions.count(FuncName);
  }

  bool isDontTouchLoc(const std::string Loc) {
    return DontTouchLocs.count(Loc);
  }

  void setDontTouchLocs(const std::string &JsonFilePath);

  friend raw_ostream &operator<<(raw_ostream &OS, const CFMSEOptions &Options) {
    OS << "CFMSEOptions : \n";
    OS << "  OnlyInLoops : " << (Options.OnlyInLoops ? "True" : "False")
       << "\n";
    OS << "  OnlySymbolicBranches : "
       << (Options.OnlySymbolicBranches ? "True" : "False") << "\n";
    OS << "  OnlyMergeDiamond : "
       << (Options.OnlyMergeDiamond ? "True" : "False") << "\n";
    OS << "  DontTouchFunctions : \n";
    for (auto FuncName : Options.DontTouchFunctions)
      OS << "    " << FuncName << "\n";
    OS << "  DontTouchLocs : \n";
    for (auto Loc : Options.DontTouchLocs)
      OS << "    " << Loc << "\n";
    return OS;
  }
};

class CFMSEPass : public PassInfoMixin<CFMSEPass> {
  CFMSEOptions Options;

public:
  CFMSEPass() = default;
  CFMSEPass(CFMSEOptions Options) : Options(Options) {}
  PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

ModulePass *createCFMSEPass();


// a pass to remove all debug info except source line numbers
class RemoveNonLineDebugInfoPass : public PassInfoMixin<RemoveNonLineDebugInfoPass> {
public:
  PreservedAnalyses run(Module &, ModuleAnalysisManager &);
};

bool removeNonLineDebugInfo(Module &M);

} // end namespace llvm

#endif // LLVM_TRANSFORMS_CFMELDER_CFMSE_H