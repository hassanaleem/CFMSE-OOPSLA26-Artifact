#!/bin/bash
ulimit -s unlimited

#define an array variable for names of benchmarks
benchNames=$(cat BenchNames_debug)

main_dir=/local/scratch/a/$USER/coreutils_debug
mkdir -p $main_dir
# iterate over benchNames and print
for benchName in $benchNames
do
    echo "Running $benchName"
    mkdir -p $main_dir/$benchName
    rm -rf $main_dir/$benchName/*
    mkdir -p $main_dir/$benchName/klee-rundir
    mkdir -p $main_dir/$benchName/cfm-rundir
    tar xzfv sandbox.tgz -C $main_dir/$benchName/klee-rundir
    tar xzfv sandbox.tgz -C $main_dir/$benchName/cfm-rundir
    ${LLVM_BUILD_DIR}/bin/opt -S -mem2reg < ./obj-llvm/src/$benchName.bc > ./obj-llvm/src/$benchName.ll
    python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -i ./obj-llvm/src/$benchName.ll -k driver_options.json -r $main_dir/$benchName > $main_dir/$benchName/driver_output_$benchName.txt 2>&1
    echo "hello" | mail -s "Done running $benchName" $USER
done
