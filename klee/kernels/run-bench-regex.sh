#!/bin/bash 
source ./run-bench-common.sh

run_bench "regex-bug" "5 10" "1" "klee"
run_bench "regex-bug" "5 10" "1" "klee_cfmsm"

echo "Done" | mail -s "regex run complete!" $USER

