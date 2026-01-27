#!/bin/bash
run=run-cfm-driver.sh

sizes=(20 25 30)
num_runs=1
# make a loop to run for different sizes
rm -rf logs
mkdir -p logs

make clean
make test-driver.bc

for runs in $(seq 1 $num_runs)
do
    mkdir logs/logs_$runs
    echo "Starting RUN $runs"

    for size in ${sizes[@]}
    do
        echo "RUnning for size $size LibOSIP"
        rm -rf cfm_driver_output
        python3 options_updater.py driver_options.json $size   
        ./"$run" > logs/logs_$runs/log_${size}.txt
        python3 ../extract_killed_states.py cfm_driver_output/libosip $size
        sleep 5

    done
done


python3 ../read_cfm_output.py logs libosip hours

