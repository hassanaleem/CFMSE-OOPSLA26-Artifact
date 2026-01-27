#!/bin/bash 
source ./run-bench-common.sh

run_bench "prim" "4 5 6" "3" "klee_cfm"
run_bench "prim" "4 5 6" "3" "klee_sm"
run_bench "prim" "4 5 6" "3" "klee_cfmsm"
run_bench "prim" "4 5 6" "1" "klee"

echo "Done" | mail -s "prim run complete!" $USER
