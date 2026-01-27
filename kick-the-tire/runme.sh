#!/bin/bash

./run-bench-toupper.sh # 10 minutes
python3 results.py -b toupper
python3 output.py