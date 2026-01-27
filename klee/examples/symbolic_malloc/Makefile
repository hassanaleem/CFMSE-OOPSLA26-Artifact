include ../makefile.in

file_name=symbolic_malloc
function_to_analzye_in_cfg=main

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} -f ${CFMSE_FLAGS} -cfmse -cfmse-print-sv -o $(file_name).ll < $(file_name).ll

include ../makefile.clean

