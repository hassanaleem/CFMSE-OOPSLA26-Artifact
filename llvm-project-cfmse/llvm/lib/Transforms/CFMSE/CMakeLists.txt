add_llvm_component_library(LLVMCFMSE
  CFMSE.cpp
  SymbolicVariableAnalysis.cpp
  CFMSELocationAnalysis.cpp
  BBReplication.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/CFMSE



  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Analysis
  Core
  Support
  CFMelder
  )

