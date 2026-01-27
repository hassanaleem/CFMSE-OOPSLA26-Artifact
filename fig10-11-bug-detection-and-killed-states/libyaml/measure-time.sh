#!/bin/bash

ulimit -s unlimited
benchName=libyaml

# Measure the time here 
time $OPT -f -cfmse -force-cfmse test-driver.bc -o test-driver-cfm.bc


