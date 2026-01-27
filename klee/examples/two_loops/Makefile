include ../makefile.in

file_name=two_loops
function_to_analzye_in_cfg=foo

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} -f ${CFMSE_FLAGS} -o $(file_name).ll < $(file_name).ll

hello: $(file_name).ll
	~/PLCL/llvm-project-rocm/build/bin/opt -enable-new-pm=0 -load ~/PLCL/llvm-project-rocm/build/lib/LLVMHello.so -hello < $(file_name).ll > /dev/null

cfg: $(file_name).ll
	${OPT} -dot-cfg $(file_name).ll
	dot -Tsvg .$(function_to_analzye_in_cfg).dot -o $(function_to_analzye_in_cfg).svg

kleeNOCFM: $(file_name).ll
	$(KLEE_BIN) --only-output-states-covering-new --write-cov $(file_name).ll

klee: $(file_name).ll
	$(KLEE_BIN) --cfmse --only-output-states-covering-new --write-cov $(file_name).ll

clean:
	rm  -rf *.ll output*.* *.dot klee-out-*/ klee-last *.svg

