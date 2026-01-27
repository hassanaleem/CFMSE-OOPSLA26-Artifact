include ../makefile.in

file_name=driver_test
function_to_analzye_in_cfg=foo

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} -f ${CFMSE_FLAGS} -o $(file_name).ll < $(file_name).ll

kleeNOCFM: $(file_name).ll
	$(KLEE_BIN) --only-output-states-covering-new --write-cov --use-cex-cache=false $(file_name).ll

klee: $(file_name).ll
	$(KLEE_BIN) --klee-cfmse --only-output-states-covering-new --write-cov $(file_name).ll

include ../makefile.clean
