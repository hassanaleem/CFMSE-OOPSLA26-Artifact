include ../makefile.in

file_name=false_positive_masking_bug
cfg_file_name=before_int
function_to_analzye_in_cfg=main

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} -f ${CFMSE_FLAGS} -o $(file_name).ll < $(file_name).ll

exec: $(file_name).c
	${CLANG} ${CLANG_EXEC_FLAGS} $(file_name).c

default: $(file_name).c
	${CLANG} ${CLANG_DEFAULT_FLAGS} $(file_name).c

hello: $(file_name).ll
	~/PLCL/llvm-project-rocm/build/bin/opt -enable-new-pm=0 -load ~/PLCL/llvm-project-rocm/build/lib/LLVMHello.so -hello < $(file_name).ll > /dev/null

cfg: $(cfg_file_name).bc
	${OPT} -dot-cfg $(cfg_file_name).bc
	dot -Tsvg .$(function_to_analzye_in_cfg).dot -o $(function_to_analzye_in_cfg)_merged.svg

cfgNOCFM: $(file_name).ll
	${OPT} -dot-cfg $(file_name).ll
	dot -Tsvg .$(function_to_analzye_in_cfg).dot -o $(function_to_analzye_in_cfg).svg

kleeNOCFM: $(file_name).ll
	$(KLEE_BIN) $(KLEE_NOCFM_OPTIONS) $(file_name).ll

klee: $(file_name).ll
	$(KLEE_BIN) $(KLEE_CFM_OPTIONS) $(file_name).ll

include ../makefile.clean
