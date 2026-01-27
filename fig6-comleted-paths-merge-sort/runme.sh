#!/bin/bash
ulimit -s unlimited
run_klee() {
    local x=$1
    rm -rf *.bc *.dot *.svg *.txt
    $CLANG -I $KLEE_INCLUDE -c -emit-llvm -Xclang -disable-O0-optnone -O0 -DSIZE="$x" merge-sort.c -o merge-sort-regular.bc
    $OPT -enable-new-pm=0 -mem2reg merge-sort-regular.bc -o merge-sort-regular.bc
    $OPT -f -cfmse -force-cfmse merge-sort-regular.bc -o merge-sort-cfmse.bc
    $KLEE --search=dfs --search=nurs:covnew -max-time=210000s -max-memory=75000 -libc=uclibc --output-dir="cfmse-size-$x" merge-sort-cfmse.bc
    $KLEE --search=dfs --search=nurs:covnew -max-time=210000s -max-memory=75000 -libc=uclibc --output-dir="regular-size-$x" merge-sort-regular.bc
}

size=(5 6 7 8 9 10)
for s in "${size[@]}"; do
    run_klee "$s"
done

python3 read_results.py
