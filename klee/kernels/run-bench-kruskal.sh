#!/bin/bash 
source ./run-bench-common.sh

run_bench "kruskal" "3 4 5" "2" "klee_cfm"
run_bench "kruskal" "3 4 5" "2" "klee_sm"
run_bench "kruskal" "3 4 5" "2" "klee_cfmsm"
run_bench "kruskal" "3 4 5" "2" "klee"

echo "Done" | mail -s "kruskal run complete!" $USER

