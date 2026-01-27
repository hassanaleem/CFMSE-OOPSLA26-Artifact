#!/bin/bash 
source ./run-bench-common.sh

run_bench "bitonic_sort" "4 8 16" "5" "klee_cfm"
run_bench "bitonic_sort" "4 8 16" "5" "klee_sm"
run_bench "bitonic_sort" "4 8 16" "5" "klee_cfmsm"
run_bench "bitonic_sort" "4 8 16" "5" "klee"
# run_bench "bitonic_sort" "4 8" "3" "klee_cfmsm_verify"
# run_bench "bitonic_sort" "16" "1" "klee_cfmsm_verify"
# run_bench "bitonic_sort" "4" "5" "klee_cfm_verify"
# run_bench "bitonic_sort" "4" "5" "klee_sm_verify"

