include ../makefile.in

file_name=lup
function_to_analzye_in_cfg=lup

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} -f ${CFMSE_FLAGS} -o $(file_name).ll < $(file_name).ll

cfg: $(file_name).ll
	${OPT} -dot-cfg $(file_name).ll
	dot -Tsvg .$(function_to_analzye_in_cfg).dot -o $(function_to_analzye_in_cfg).svg

kleeNOCFM: $(file_name).ll
	$(KLEE_BIN) --libc=uclibc --posix-runtime $(KLEE_NOCFM_OPTIONS) $(file_name).ll

klee: $(file_name).ll
	$(KLEE_BIN) --libc=uclibc --posix-runtime $(KLEE_CFM_OPTIONS)  $(file_name).ll

include ../makefile.clean
