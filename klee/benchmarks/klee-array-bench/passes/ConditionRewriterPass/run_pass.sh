#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 program.bc <optimized_filename>"
  exit 1
fi

opt -load ../build/ConditionRewriterPass/libSRGLLVMConditionRewriterPass.so -a2i $1 > $2
