#!/bin/bash
ulimit -s unlimited

#define an array variable for names of benchmarks
benchNames=$(cat BenchNames)

main_dir=/local/scratch/a/$USER/bandicoot
mkdir -p $main_dir
# iterate over benchNames and print
for benchName in $benchNames
do
    echo "Running $benchName"
    mkdir -p $main_dir/$benchName
    rm -rf $main_dir/$benchName/*
    mkdir -p $main_dir/$benchName/klee-rundir
    mkdir -p $main_dir/$benchName/cfm-rundir
    cp test.env $main_dir/$benchName/
    tar xzfv sandbox.tgz -C $main_dir/$benchName/klee-rundir
    tar xzfv sandbox.tgz -C $main_dir/$benchName/cfm-rundir
    python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./bin/$benchName.bc -k driver_options.json -r $main_dir/$benchName > $main_dir/$benchName/driver_output_$benchName.txt 2>&1

done
echo "hello" | mail -s "bandicoot all done!" $USER
