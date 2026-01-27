#!/bin/bash 
source ./run-bench-common.sh

run_bench "detect_edges" "3 4 5" "2" "klee_cfm"
run_bench "detect_edges" "3 4 5" "2" "klee_sm"
run_bench "detect_edges" "3 4 5" "2" "klee_cfmsm"
run_bench "detect_edges" "3 4 5" "1" "klee"

echo "Done" | mail -s "detect_edges run complete!" $USER
