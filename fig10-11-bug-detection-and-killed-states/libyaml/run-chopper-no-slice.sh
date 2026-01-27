#!/bin/bash

ulimit -s unlimited

time klee \
    --output-dir=out-chopper-no-slice \
    -max-time=3600 \
    -max-memory=4096 \
    -libc=uclibc \
    -simplify-sym-indices \
    -search=nurs:covnew \
    -split-search \
    -skip-functions=yaml_parser_update_buffer:864,yaml_parser_fetch_stream_start:870 \
    -use-slicer=0 \
    test-driver.bc 64
