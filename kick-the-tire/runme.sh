#!/bin/bash

rm -rf toupper.csv table3.csv
./run-bench-toupper.sh # 3 minutes
python3 results.py -b toupper
python3 output.py
