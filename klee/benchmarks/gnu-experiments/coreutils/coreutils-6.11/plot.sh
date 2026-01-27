    
#!/bin/bash
ulimit -s unlimited
directories=$(ls cfm_driver_output_plots_old/)
main_dir=$(realpath .)/cfm_driver_output_plots_old
cd $main_dir

echo directories are $directories
for directories in $directories
do
    if [ -d "$directories" ]; then
        benchName=$(basename "$directories")
        echo "Plotting for $main_dir/$benchName"
        awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-cfm-*/coverage.csv > "$main_dir/$benchName/coverage-cfmse.csv"
        awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$benchName"/klee-nocfm-*/coverage.csv > "$main_dir/$benchName/coverage-nocfmse.csv"
        python3 ${KLEE_BUILD_DIR}/../scripts/coverage_graph.py $main_dir/$benchName/coverage-cfmse.csv $main_dir/$benchName/coverage-nocfmse.csv

    fi
    # awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$main_dir/$benchName"/klee-cfm-*/coverage.csv > "$main_dir/$main_dir/$benchName/coverage-cfmse.csv"
    # awk 'FNR==1 && NR!=1 {next} {print}' "$main_dir/$main_dir/$benchName"/klee-nocfm-*/coverage.csv > "$main_dir/$main_dir/$benchName/coverage-nocfmse.csv"

    # python3 ${KLEE_BUILD_DIR}/../scripts/coverage_graph.py $main_dir/$main_dir/$benchName/coverage-cfmse.csv $main_dir/$main_dir/$benchName/coverage-nocfmse.csv
done
