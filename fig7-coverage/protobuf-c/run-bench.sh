#!/bin/bash
ulimit -s unlimited

#define an array variable for names of benchmarks
./build-bench-llvm.sh
benchNames=test_deserialize

main_dir=$(realpath .)/cfm_driver_output

# mkdir -p $main_dir
# iterate over benchNames and print
for benchName in $benchNames
do
    echo "Running $benchName"
    $CLANG -I $KLEE_INCLUDE -I. -I/artifact/fig7-coverage/protobuf-c/install/include -g -c -emit-llvm -O0 -Xclang -disable-O0-optnone $benchName.c -o $benchName.bc
    $LLVM_BUILD_DIR/bin/llvm-link $benchName.bc protobuf-c.bc amessage.pb-c.bc -o $benchName.bc
    mkdir -p $main_dir/$benchName
    rm -rf $main_dir/$benchName/*
    mkdir -p $main_dir/$benchName/klee-rundir
    mkdir -p $main_dir/$benchName/cfm-rundir
    mkdir -p $main_dir/$benchName/klee-rundir/sandbox
    mkdir -p $main_dir/$benchName/cfm-rundir/sandbox
    ${LLVM_BUILD_DIR}/bin/opt -mem2reg $benchName.bc -o $benchName.opt.bc
    python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i $benchName.opt.bc -k driver_options.json -r $main_dir/$benchName > $main_dir/$benchName/driver.txt 2>&1


    awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-cfm-*/coverage.csv > "$main_dir/$benchName/coverage-cfmse.csv"
    awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-nocfm-*/coverage.csv > "$main_dir/$benchName/coverage-nocfmse.csv"

    python3 coverage_graph.py $main_dir/$benchName/coverage-cfmse.csv $main_dir/$benchName/coverage-nocfmse.csv

done
# echo "hello" | mail -s "utf8 all done!" $USER
