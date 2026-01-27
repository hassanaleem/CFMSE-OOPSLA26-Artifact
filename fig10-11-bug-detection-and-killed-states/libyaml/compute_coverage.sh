#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: <klee_out_dir>"
    exit 1
fi

KLEE_OUT_DIR=$1
INPUT_SIZE=64

for f in ./${KLEE_OUT_DIR}/*.ktest; do
    ktest-tool -d "$f.data" $f
    ./test-driver-gcov ${INPUT_SIZE} "$f.data"
done
