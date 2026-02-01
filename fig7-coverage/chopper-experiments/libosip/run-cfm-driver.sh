#!/bin/bash

ulimit -s unlimited
make clean
make test-driver.bc


benchName=libosip

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
python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./test-driver.bc -k driver_options.json -r $main_dir/$benchName > $main_dir/$benchName/driver.txt 2>&1

python3 ${KLEE_BUILD_DIR}/../scripts/coverage_graph.py $main_dir/$benchName/klee-cfm-*/coverage.csv $main_dir/$benchName/klee-nocfm-*/coverage.csv
#echo "hello" | mail -s "Done running $benchName" $USER

mv *.pdf libosip-coverage.pdf
