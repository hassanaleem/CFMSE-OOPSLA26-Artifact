# Installation Instructions

This demo assumes a Unix-like system. This was tested on `Ubuntu 22.04.3 LTS`.

Installation requires `cmake (>= 3.13.4)` and `build-essential`.

## Installing LLVM

First, setup the experiment directory
```
export EXPERIMENT_HOME=$(realpath .)
```

Install `LLVM` using (takes minutes in a 128 core machine),
```
cd ${EXPERIMENT_HOME}
git clone https://github.com/charitha22/llvm-project-rocm.git llvm-project
cd llvm-project
git checkout origin/cfmse-llvm-14
cmake -G Ninja -B build_cfmse -S llvm \
   -DLLVM_ENABLE_PROJECTS="clang" \
   -DLLVM_BUILD_EXAMPLES=ON \
   -DLLVM_TARGETS_TO_BUILD="X86" \
   -DCMAKE_BUILD_TYPE=Release \
   -DLLVM_ENABLE_ASSERTIONS=ON \
   -DCMAKE_CXX_COMPILER=clang++ \
   -DLLVM_USE_LINKER=gold \
  -DCMAKE_INSTALL_PREFIX=${EXPERIMENT_HOME}/llvm-project/install
```

## Installing KLEE

Install required dependencies using,
```
sudo apt-get install cmake bison flex libboost-all-dev python perl zlib1g-dev minisat
```

Install `klee-uclibc` (requires `python` in PATH),
```
cd ${EXPERIMENT_HOME}
git clone https://github.com/klee/klee-uclibc.git
cd klee-uclibc
git checkout 9351bdc9ad61ba25b051bef36f78b709ba50ff28
./configure --make-llvm-lib --with-cc ${EXPERIMENT_HOME}/llvm-project-rocm/build_cfmse/bin/clang --with-llvm-config ${EXPERIMENT_HOME}/llvm-project-rocm/build_cfmse/bin/llvm-config
make -j4
```

Install `minisat`,
```
cd ${EXPERIMENT_HOME}
git clone https://github.com/stp/minisat.git
cd minisat
git checkout 37158a35c62d448b3feccfa83006266e12e5acb7
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr/local/ ../
sudo make install
```

Install `stp`,
```
cd ${EXPERIMENT_HOME}
git clone https://github.com/stp/stp.git
cd stp
git checkout tags/2.3.3
mkdir build
cd build
cmake ..
make
sudo make install
```

Finally, install `klee`,
```
cd ${EXPERIMENT_HOME}
git clone git@github.com:charitha22/klee.git 
cd klee
git checkout origin/cfmse
mkdir build
cd build
cmake -DENABLE_SOLVER_STP=ON  -DENABLE_POSIX_RUNTIME=ON  -DENABLE_KLEE_UCLIBC=ON -DKLEE_UCLIBC_PATH=${EXPERIMENT_HOME}/klee-uclibc/ -DLLVM_CONFIG_BINARY=${EXPERIMENT_HOME}/llvm-project-rocm/build_cfmse/bin/llvm-config -DLLVMCC=${EXPERIMENT_HOME}/llvm-project-rocm/build_cfmse/bin/clang -DLLVMCXX=${EXPERIMENT_HOME}/llvm-project-rocm/build_cfmse/bin/clang++ ../
make -j4
```
# Running the Demo

First, setup some environment variables so the run scripts know where to find `klee`, `clang` etc.
```
cd ${EXPERIMENT_HOME}/klee
source scripts/setup_env.sh
```
## `toupper` (Running example)
```
cd ${EXPERIMENT_HOME}/klee/demo/toupper
. run-bench-toupper.sh
```
This will run the `K`, `C`, `SM` and `C-SM` variants and print out the results in `csv` format corresponding to the `toupper` benchmark shown in Table 2 of the paper. 


## `libosip` Case Study

Run following commands to reproduce the results of the `libosip` case study described in the paper. This will take more the 1 hour to complete.
```
cd ${EXPERIMENT_HOME}/klee/demo/libosip
make test-driver.bc
. run-cfm-driver.sh
```

Once driver execution finishes (after righly 1 hour), use following to generate the coverage plot in PDF format.
```
cd ${EXPERIMENT_HOME}/klee/demo/libosip
python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/coverage.py cfm_driver_output/libosip/
```