#!/bin/bash 
source ./run-bench-common.sh

run_bench "transitive_closure" "3 4 5" "2" "klee_cfm"
run_bench "transitive_closure" "3 4 5" "2" "klee_sm"
run_bench "transitive_closure" "3 4 5" "2" "klee_cfmsm"
run_bench "transitive_closure" "3 4 5" "1" "klee"

echo "Done" | mail -s "transitive_closure run complete!" $USER

