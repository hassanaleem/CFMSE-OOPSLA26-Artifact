#!/bin/bash
run=run-cfm-driver.sh

sizes=(9 10 11 12 13)
num_runs=3
# make a loop to run for different sizes
rm -rf logs
mkdir -p logs
for runs in $(seq 1 $num_runs)
do
    mkdir logs/logs_$runs
    echo "Starting RUN $runs"

    for size in ${sizes[@]}
    do
        echo "RUnning for size $size Regex"
        rm -rf test-driver.bc cfm_driver_output/
        $CLANG -I $KLEE_INCLUDE -emit-llvm -S -Xclang -disable-O0-optnone -g -DSIZE=$size re.c -o test-driver.bc
        # log output of run.sh
        ./"$run" > logs/logs_$runs/log_${size}.txt
        sleep 5

    done
done


python3 ../read_cfm_output.py logs regex seconds

