#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 program.bc"
  exit 1
fi

opt -load ../build/ArrayPass/libSRGLLVMArrayPass.so -print_arrays $1 > /dev/null
