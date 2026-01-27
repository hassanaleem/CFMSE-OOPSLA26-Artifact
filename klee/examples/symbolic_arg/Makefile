include ../makefile.in
file_name=symbolic_arg

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} ${CFMSE_FLAGS} -cfmse -cfmse-print-sv < $(file_name).ll > $(file_name).merged.ll

include ../makefile.clean
