#!/bin/bash 
source ./run-bench-common.sh

run_bench "merge_sort" "5 10 15" "5" "klee_cfm"
run_bench "merge_sort" "5 10 15" "5" "klee_sm"
run_bench "merge_sort" "5 10 15" "5" "klee_cfmsm"
run_bench "merge_sort" "5 10 15" "5" "klee"

echo "Done" | mail -s "merge_sort run complete!" $USER

