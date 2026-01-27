#!/bin/bash

ulimit -s unlimited
make clean
make test.bc

# mkdir -p /local/scratch/a/cgusthin/libtasn1_CVE-2012-1569
# python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i test.bc -k driver_options.json -r /local/scratch/a/cgusthin/libtasn1_CVE-2012-1569

# echo "Done" | mail -s "libtasn1 run complete!" $USER
# echo "Done" | mail -s "libosip run complete!" $USER

benchName=libtasn

main_dir=$(realpath .)/cfm_driver_output
mkdir -p $main_dir

echo "Running $benchName"
mkdir -p $main_dir/$benchName
rm -rf $main_dir/$benchName/*
mkdir -p $main_dir/$benchName/klee-rundir
mkdir -p $main_dir/$benchName/cfm-rundir
# create empty sandbox directories for this benchmark

mkdir -p $main_dir/$benchName/klee-rundir/sandbox
cp def.asn $main_dir/$benchName/klee-rundir/sandbox/ #def.asn needed as input file

mkdir -p $main_dir/$benchName/cfm-rundir/sandbox
cp def.asn $main_dir/$benchName/cfm-rundir/sandbox/ #def.asn needed as input file
python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i test.bc -k driver_options.json -r $main_dir/$benchName > $main_dir/$benchName/driver_output_$benchName.txt 2>&1


# combine all files into one coverage graph
awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-cfm-*/coverage.csv > "$main_dir/$benchName/coverage-cfmse.csv"
awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-nocfm-*/coverage.csv > "$main_dir/$benchName/coverage-nocfmse.csv"
python3 ${KLEE_BUILD_DIR}/../scripts/coverage_graph.py $main_dir/$benchName/coverage-cfmse.csv $main_dir/$benchName/coverage-nocfmse.csv
