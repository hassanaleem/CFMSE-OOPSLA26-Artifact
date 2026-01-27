include ../makefile.in
file_name=simple_dataflow

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} ${CFMSE_FLAGS} -cfmse -cfmse-print-sv < $(file_name).ll > /dev/null

include ../makefile.clean
