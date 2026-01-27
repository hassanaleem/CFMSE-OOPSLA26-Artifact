#!/bin/bash

KLEE=${KLEE_BUILD_DIR}/bin/klee
OPT=${LLVM_BUILD_DIR}/bin/opt

#BENCHMARKS=$(cat BenchNames)
BENCHMARKS=wc

cd obj-llvm/src


for BENCH in ${BENCHMARKS}; do
  echo "Program name : ${BENCH}"
   #${KLEE} --libc=uclibc --posix-runtime ./${BENCH}.bc --sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 --sym-stdin 8 --sym-stdout 
  ${OPT} -mem2reg -S < ${BENCH}.bc > ${BENCH}.opt.ll
  ${KLEE} --simplify-sym-indices --write-cvcs --write-cov --output-module \
      --max-memory=1000 --disable-inlining --use-forked-solver \
      --use-cex-cache --libc=uclibc --posix-runtime \
      --external-calls=all --only-output-states-covering-new \
      --max-sym-array-size=4096 --max-solver-time=30s --max-time=60min \
      --max-memory-inhibit=false --max-static-fork-pct=1 \
      --max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal \
      --search=random-path --search=nurs:covnew \
      --use-batching-search --batch-instructions=10000 \
      --klee-cfmse --klee-cfmse-loads-symbolic \
      ./${BENCH}.opt.ll --sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 --sym-stdin 8 --sym-stdout
done
