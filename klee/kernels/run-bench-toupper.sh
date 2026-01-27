#!/bin/bash 
source ./run-bench-common.sh


run_bench "toupper" "10 50 100" "2" "klee_cfm"
run_bench "toupper" "10 50 100" "2" "klee_sm"
run_bench "toupper" "10 50 100" "2" "klee_cfmsm"
run_bench "toupper" "10 50 100" "1" "klee"
# run_bench "toupper" "10 50 100" "1" "klee_verify"

echo "Done" | mail -s "toupper run complete!" $USER
