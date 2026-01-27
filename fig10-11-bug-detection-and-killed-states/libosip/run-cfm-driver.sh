#!/bin/bash
ulimit -s unlimited

# #define an array variable for names of benchmarks
# do all this thrice
benchName=libosip

main_dir=$(realpath .)/cfm_driver_output
mkdir -p $main_dir
# mkdir -p logs

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
# mv cfm_driver_output logs/



# main_dir=$(realpath .)/cfm_driver_output_2
# mkdir -p $main_dir

# echo "Running $benchName"
# mkdir -p $main_dir/$benchName
# rm -rf $main_dir/$benchName/*
# mkdir -p $main_dir/$benchName/klee-rundir
# mkdir -p $main_dir/$benchName/cfm-rundir
# # create empty sandbox directories for this benchmark
# mkdir -p $main_dir/$benchName/klee-rundir/sandbox
# mkdir -p $main_dir/$benchName/cfm-rundir/sandbox
# python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./test-driver.bc -k driver_options_2.json -r $main_dir/$benchName > $main_dir/$benchName/driver.txt 2>&1
# mv cfm_driver_output_2 logs/



# # main_dir=$(realpath .)/cfm_driver_output
# # mkdir -p $main_dir

# # echo "Running $benchName"
# # mkdir -p $main_dir/$benchName
# # rm -rf $main_dir/$benchName/*
# # mkdir -p $main_dir/$benchName/klee-rundir
# # mkdir -p $main_dir/$benchName/cfm-rundir
# # # create empty sandbox directories for this benchmark
# # mkdir -p $main_dir/$benchName/klee-rundir/sandbox
# # mkdir -p $main_dir/$benchName/cfm-rundir/sandbox
# # python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./test-driver.bc -k driver_options_1.json -r $main_dir/$benchName > $main_dir/$benchName/driver.txt 2>&1
# # mv cfm_driver_output_1 logs/


python3 ../read_cfm_output.py logs libosip hours


