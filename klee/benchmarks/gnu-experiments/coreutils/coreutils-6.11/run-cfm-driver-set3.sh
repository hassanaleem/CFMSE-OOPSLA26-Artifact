#!/bin/bash
ulimit -s unlimited

# #define an array variable for names of benchmarks
benchNames=$(cat BenchNames5)

main_dir=$(realpath .)/cfm_driver_output_plots_old
# mkdir -p $main_dir
# iterate over benchNames and print
for benchName in $benchNames
do
    # echo "Running $benchName"
    # mkdir -p $main_dir/$benchName
    # rm -rf $main_dir/$benchName/*
    # mkdir -p $main_dir/$benchName/klee-rundir
    # mkdir -p $main_dir/$benchName/cfm-rundir
    # # mkdir -p $main_dir/$benchName/klee-rundir/sandbox
    # # mkdir -p $main_dir/$benchName/cfm-rundir/sandbox
    # tar xzfv sandbox.tgz -C $main_dir/$benchName/klee-rundir
    # tar xzfv sandbox.tgz -C $main_dir/$benchName/cfm-rundir

    # python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./obj-llvm/src/$benchName.bc -k driver_options.json -r $main_dir/$benchName > $main_dir/$benchName/driver_output_$benchName.txt 2>&1

    awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-cfm-*/coverage.csv > "$main_dir/$benchName/coverage-cfmse.csv"
    awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-nocfm-*/coverage.csv > "$main_dir/$benchName/coverage-nocfmse.csv"

    python3 ${KLEE_BUILD_DIR}/../scripts/coverage_graph.py $main_dir/$benchName/coverage-cfmse.csv $main_dir/$benchName/coverage-nocfmse.csv

    # echo "hello" | mail -s "Done running $benchName" $USER
done
