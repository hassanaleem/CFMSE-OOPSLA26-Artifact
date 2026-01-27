#!/bin/bash 
source ./run-bench-common.sh

run_bench "floyd_warshall" "3 4 5" "5" "klee_cfm"
run_bench "floyd_warshall" "3 4 5" "5" "klee_sm"
run_bench "floyd_warshall" "3 4 5" "5" "klee_cfmsm"
run_bench "floyd_warshall" "3 4 5" "5" "klee"

echo "Done" | mail -s "floyd_warshall run complete!" $USER
