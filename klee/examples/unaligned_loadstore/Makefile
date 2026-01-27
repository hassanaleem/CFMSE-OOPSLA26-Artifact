include ../makefile.in
file_name=unaligned_loadstore

all: $(file_name).c
	${CLANG} ${CLANG_FLAGS} $(file_name).c
	${OPT} ${CFMSE_FLAGS} -cf-merging-similarity-threshold=0.0 < $(file_name).ll > $(file_name).merged.ll

kleeNOCFM: $(file_name).ll
	${KLEE} $(file_name).ll

klee: $(file_name).merged.ll
	${KLEE} $(file_name).merged.ll

include ../makefile.clean
