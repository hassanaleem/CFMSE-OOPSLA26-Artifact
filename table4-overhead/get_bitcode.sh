#!/bin/bash


# CFLAGS = "-g -O0 -Xclang -disable-O0-optnone -emit-llvm" 
libosip="/artifact/fig7-coverage/chopper-experiments/libosip"

cd $libosip
make clean
make test-driver.bc
mv test-driver.bc /artifact/table4-overhead/libosip.bc
make clean
cd -
# Measure timne it takes to run opt pass

$OPT -f -cfmse -time-passes libosip.bc -o libosip_opt.bc > libosip.txt 2>&1

echo "Done libosip"


