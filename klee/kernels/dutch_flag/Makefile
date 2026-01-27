include ../makefile.in

file_name=df
function_to_analzye_in_cfg=flag

all : nosm sm

nosm: $(file_name).c
	${CLANG} ${CLANG_FLAGS} -DSIZE=$(SIZE) $^
	${OPT} -f ${CFMSE_FLAGS} -o $(file_name)_nosm.ll < $(file_name).ll

sm: $(file_name).c
	${CLANG} ${CLANG_FLAGS} -DSIZE=$(SIZE) -DMERGE $^
	${OPT} -f ${CFMSE_FLAGS} -o $(file_name)_sm.ll < $(file_name).ll

cfg: $(file_name).ll
	${OPT} -dot-cfg $^
	dot -Tsvg .$(function_to_analzye_in_cfg).dot -o $(function_to_analzye_in_cfg).svg

klee: $(file_name)_nosm.ll
	time $(KLEE_BIN) $(KLEE_NOCFM_OPTIONS) $^

klee_sm: $(file_name)_sm.ll
	time $(KLEE_BIN) -use-merge $(KLEE_NOCFM_OPTIONS) $^

klee_cfm: $(file_name)_nosm.ll
	time $(KLEE_BIN) $(KLEE_CFM_OPTIONS) $^

klee_cfmsm: $(file_name)_sm.ll
	time $(KLEE_BIN) -use-merge $(KLEE_CFM_OPTIONS) $^

include ../makefile.clean