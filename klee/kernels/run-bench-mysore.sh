#!/bin/bash 
source ./run-bench-common.sh

run_bench "mysore" "2 3 4" "2" "klee_cfm"
run_bench "mysore" "2 3 4" "2" "klee_sm"
run_bench "mysore" "2 3 4" "2" "klee_cfmsm"
run_bench "mysore" "2 3 4" "2" "klee"
