#!/bin/bash
ulimit -s unlimited

#define an array variable for names of benchmarks
benchName=tcc

main_dir=/local/scratch/a/$USER/tcc_noexit
mkdir -p $main_dir

echo "Running $benchName"
mkdir -p $main_dir/$benchName
rm -rf $main_dir/$benchName/*
mkdir -p $main_dir/$benchName/klee-rundir
mkdir -p $main_dir/$benchName/cfm-rundir

env -i /bin/bash -c '(source ../../testing-env.sh; env >test.env)'
mv test.env $main_dir/$benchName
tar xzf ../../sandbox.tgz 
mv sandbox $main_dir/$benchName/klee-rundir
tar xzf ../../sandbox.tgz 
mv sandbox $main_dir/$benchName/cfm-rundir

# dry run
# python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -d -i ./obj-llvm/tcc.bc -k driver_options.json -r $main_dir/$benchName

${LLVM_BUILD_DIR}/bin/opt ./obj-llvm/tcc.bc -mem2reg -S -o ./obj-llvm/tcc.ll
python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./obj-llvm/tcc.ll -k driver_options.json -r $main_dir/$benchName > $main_dir/$benchName/driver_output_$benchName.txt 2>&1
echo "hello" | mail -s "Done running $benchName" $USER
