#!/bin/bash 
source ./run-bench-common.sh

run_bench "connected_comp" "3 4 5" "2" "klee_cfm"
run_bench "connected_comp" "3 4 5" "2" "klee_sm"
run_bench "connected_comp" "3 4 5" "2" "klee_cfmsm"
run_bench "connected_comp" "3 4 5" "2" "klee"

echo "Done" | mail -s "connected_comp run complete!" $USER

