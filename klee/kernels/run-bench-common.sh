BENCH_OUT_HOME=$HOME/local/scratch/a/$USER/cfmse-experiments
source ~/klee/python3-venv/bin/activate

function run_bench  {
    echo "Running $1"
    # check if the directory exists
    if [ ! -d "$1" ]; then
        echo "Directory $1 does not exist"
        exit 1
    fi

    cd $1
    # rm -f *.log *.csv
    
    # create a unique output directory for this run
    OUTPUT_DIR_FOR_THIS_RUN=$BENCH_OUT_HOME/$(date +%m%d%Y_%H%M%S)_"$1"_"$4"
    mkdir -p $OUTPUT_DIR_FOR_THIS_RUN
    echo "Output directory: $OUTPUT_DIR_FOR_THIS_RUN"

    for input_size in $2; do
        echo "Input size: $input_size"
        make clean > compile_$input_size.log 2>&1
        SIZE=$input_size make all >> compile_$input_size.log 2>&1
         
        for i in $(seq 1 $3); do
            echo "Run $i"
            echo "running $4"
                
            OUTPUT_DIRNAME=$OUTPUT_DIR_FOR_THIS_RUN/"$4"_"$input_size"_"$i"
            
            OUTPUT_DIR=$OUTPUT_DIRNAME make "$4" > "$4"_"$input_size"_"$i".log 2>&1
            cat $OUTPUT_DIRNAME/info >> "$4"_"$input_size"_"$i".log 2>&1
            ${KLEE_BUILD_DIR}/bin/klee-stats --print-all --table-format=csv $OUTPUT_DIRNAME > "$4"_stats_"$input_size"_"$i".csv 2>&1
        done
    done
    cd ..
}

