#!/bin/bash
ulimit -s unlimited

#define an array variable for names of benchmarks
benchName=json_test

main_dir=$(realpath .)/cfm_driver_output
rm -rf json_test.bc json_test.opt.bc
$CLANG -I $KLEE_INCLUDE -g -c -emit-llvm -O0 -Xclang -disable-O0-optnone json_test.c -o json_test.bc

mkdir -p $main_dir
# iterate over benchNames and print

echo "Running $benchName"
mkdir -p $main_dir/$benchName
rm -rf $main_dir/$benchName/*
mkdir -p $main_dir/$benchName/klee-rundir
mkdir -p $main_dir/$benchName/cfm-rundir
mkdir -p $main_dir/$benchName/klee-rundir/sandbox
mkdir -p $main_dir/$benchName/cfm-rundir/sandbox
${LLVM_BUILD_DIR}/bin/opt -mem2reg $benchName.bc > $benchName.opt.bc
python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i $benchName.opt.bc -k driver_options.json -r $main_dir/$benchName


# combine results from all run
awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-cfm-*/coverage.csv > "$main_dir/$benchName/coverage-cfmse.csv"
awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-nocfm-*/coverage.csv > "$main_dir/$benchName/coverage-nocfmse.csv"
python3 ${KLEE_BUILD_DIR}/../scripts/coverage_graph.py $main_dir/$benchName/coverage-cfmse.csv $main_dir/$benchName/coverage-nocfmse.csv


# echo "hello" | mail -s "utf8 all done!" $USER
