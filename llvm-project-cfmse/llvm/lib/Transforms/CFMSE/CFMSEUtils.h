#ifndef LLVM_LIB_TRANSFORMS_CFMSE_UTILS_H
#define LLVM_LIB_TRANSFORMS_CFMSE_UTILS_H

// #define CFMSE_DEBUG

#define INFO(x) do { errs() << "INFO[cfmse]: " << x; } while (0)


#ifdef CFMSE_DEBUG

#define DEBUG(x) do { errs() << "DEBUG[cfmse] : " << x; } while (0)

#else

#define DEBUG(x)

#endif

#endif