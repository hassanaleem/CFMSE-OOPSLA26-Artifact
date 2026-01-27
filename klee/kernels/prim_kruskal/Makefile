include ../makefile.in

file_name=prim_kruskal
function_to_analzye_in_cfg=primMST

KLEE_EXTRA_OPTIONS=$(KLEE_LIBC_FLAGS)
CFM_EXTRA_OPTIONS=--klee-cfmse-run-only-on-loops=false

include ../makefile.common

include ../makefile.clean
