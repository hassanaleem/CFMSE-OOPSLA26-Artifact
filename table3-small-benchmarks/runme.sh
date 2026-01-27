#!/bin/bash
ulimit -s unlimited


./run-bench-toupper.sh # 10 minutes
python3 results.py -b toupper

./run-bench-bitonic_sort.sh # 12 minutes
python3 results.py -b bitonic_sort

./run-bench-connected-comp.sh # 
python3 results.py -b connected_comp

./run-bench-prim.sh
python3 results.py -b prim

./run-bench-merge_sort.sh # 40 minutes to run with 1m timeout
python3 results.py -b merge_sort

./run-bench-transitive_closure.sh
python3 results.py -b transitive_closure

./run-bench-dilation.sh
python3 results.py -b dilation

./run-bench-detect-edges.sh
python3 results.py -b detect_edges

./run-bench-floyd_warshall.sh
python3 results.py -b floyd_warshall

./run-bench-erosion.sh
python3 results.py -b erosion

python3 output.py



