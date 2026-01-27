# Optimizing symbolic execution for arrays

## Case studies
1. bandicoot
2. bc
3. binutils
4. coreutils
5. findutils
6. sharutils
7. tcc

### Configure
Edit `case_studies/common.mk` with your environment
```makefile
##
## OTHER COMMANDS
##
UNAME:=$(shell uname)
SHELL:=/bin/bash
GIT:=git

##
## LLVM
##
LLVM_CONFIG:=llvm-config
CLANG:=clang
CLANGXX:=clang++
LLVM_COMPILER:=$(CLANG)
OPT:=opt
```
In case you already have `wllvm` and `klee` (with array optimizations), it is possible to configure these variables:
```makefile
##
## WLLVM
##
WLLVMROOT=$(TOOLS)/whole-program-llvm
WLLVM=$(WLLVMROOT)/wllvm
EXTRACTBC=$(WLLVMROOT)/extract-bc

##
## KLEE
##
[...]
KLEE_DIR=$(ROOT)/case_studies/tools/klee
KLEE_BIN=$(KLEE_DIR)/Release+Asserts/bin
KLEE=$(KLEE_BIN)/klee
```

### Compile the case study
Enter in the experiment directory (e.g. `coreutils`) and invoke `make`
```shell
cd case_studies/coreutils
make
```
The source code of the case study should be downloaded, patched, configured, and compiled with WLLVM automatically.

### Run experiments
To create the baseline run (e.g. with DFS search and for 30 minutes) invoke
```shell
make KSEARCH=dfs KTIMEOUT=1800. create-baseline
```
To run one single program (e.g. with DFS search and for 30 minutes) invoke
```shell
make KSEARCH=dfs KTIMEOUT=1800. baseline-klee-base64
```
To run one entire deterministic experiment (either DFS or BFS) invoke
```shell
make all-dfs
```

### Check experiments
Use the script `compare.sh` in the directory `case_studies` to obtain some statistics
```shell
cd case_studies/binutils
sh ../compare.sh original/klee-out-ar optimized/klee-out-ar
```
An example of the output is
```shell
--------------------------------------------------------------------------
a2abd181
a2abd181
--------------------------------------------------------------------------
1.167080e+03
1.079422e+03
--------------------------------------------------------------------------
KLEE: done: explored paths = 872
KLEE: done: explored paths = 872
KLEE: done: avg. constructs per query = 82
KLEE: done: avg. constructs per query = 85
KLEE: done: total queries = 545
KLEE: done: total queries = 545
KLEE: done: valid queries = 253
KLEE: done: valid queries = 253
KLEE: done: invalid queries = 292
KLEE: done: invalid queries = 292
KLEE: done: query cex = 545
KLEE: done: query cex = 545
KLEE: done: total instructions = 3488967904
KLEE: done: total instructions = 3488967904
KLEE: done: completed paths = 650
KLEE: done: completed paths = 650
KLEE: done: generated tests = 4
KLEE: done: generated tests = 4
```
The first two lines are the CRC code of `instructions.txt.gz`. If the two CRCs differ, the execution diverged.
Then then second paragraph shows the elapsed time for the execution (Wall time) as obtained from `run.stats`.
The last part of the output compare some statistics taken from `info`.

---
### Compile passes
```shell
cd passes
mkdir build
cd build
cmake ..
make
```
#### Run ArrayPass
Run ArrayPass on the toy example simple_test.c
```shell
cd passes/build
sh ArrayPass/run.sh
```
Run ArrayPass on other examples
```shell
clang -emit-llvm -c -g example.c
opt -load passes/build/ArrayPass/libSRGLLVMArrayPass.so -print_arrays example.bc > /dev/null
```
---
#### Run ConditionRewriterPass
```shell
clang -emit-llvm -c -g example.c
opt -load passes/build/ConditionRewriterPass/libSRGLLVMConditionRewriterPass.so -a2i example.bc > /dev/null
```
