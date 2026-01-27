#!/bin/bash
ulimit -s unlimited

#define an array variable for names of benchmarks
benchName=utf

main_dir=$(realpath .)/cfm_driver_output
mkdir -p $main_dir

echo "Running $benchName"
mkdir -p $main_dir/$benchName
rm -rf $main_dir/$benchName/*
mkdir -p $main_dir/$benchName/klee-rundir
mkdir -p $main_dir/$benchName/cfm-rundir
# create empty sandbox directories for this benchmark
mkdir -p $main_dir/$benchName/klee-rundir/sandbox
mkdir -p $main_dir/$benchName/cfm-rundir/sandbox
python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./test-driver.bc -k driver_options.json -r $main_dir/$benchName
#echo "hello" | mail -s "Done running $benchName" $USER
