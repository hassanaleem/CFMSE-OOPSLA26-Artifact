#!/bin/bash 
source ./run-bench-common.sh

run_bench "erosion" "4 5 6" "5" "klee_cfm"
run_bench "erosion" "4 5 6" "5" "klee_sm"
run_bench "erosion" "4 5 6" "5" "klee_cfmsm"
run_bench "erosion" "4 5 6" "5" "klee"

#run_bench "erosion" "4 5 6" "5" "klee_cfm_verify"
#run_bench "erosion" "4 5 6" "5" "klee_sm_verify"
#run_bench "erosion" "4 5 6" "5" "klee_cfmsm_verify"
#run_bench "erosion" "4 5" "3" "klee_verify"
#run_bench "erosion" "6" "1" "klee_verify"

