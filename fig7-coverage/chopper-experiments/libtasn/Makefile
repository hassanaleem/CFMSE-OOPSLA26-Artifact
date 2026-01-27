ROOT=$(realpath ..)
include $(ROOT)/common.mk

.SILENT:

SRC_PATH=./libtasn1-2.11/

INCLUDES=-I $(KLEE_SRC_DIR)/include -I $(SRC_PATH) -I $(SRC_PATH)/lib -I $(SRC_PATH)/lib/gllib
DEFINES=-D_GNU_SOURCE -DSIZEOF_UNSIGNED_INT=4 -DSIZEOF_UNSIGNED_LONG_INT=8 -DASN1_BUILDING

CFLAGS=-emit-llvm -c -g $(DEFINES) $(INCLUDES)
LDFLAGS=

%.bc: %.c
	$(CLANG) $(CFLAGS) $< -o $@

SOURCES=$(shell ls $(SRC_PATH)/lib/*.c) main.c
DEPS=$(patsubst %.c,%.o,$(SOURCES))
BC_DEPS=$(patsubst %.c,%.bc,$(SOURCES))

TARGET=test.bc

all: $(TARGET)

$(TARGET): $(BC_DEPS)
	$(LINK) $^ -o $@
	$(OPT) -mem2reg $@ -o $@
	$(DIS) $@

all-experiments: all-klee all-cse

all-klee: run-klee-random run-klee-dfs run-klee-coverage

run-klee-random: $(TARGET)
	echo "** Running KLEE with random search"
	-$(KLEE) \
	--libc=uclibc --posix-runtime \
	--search=random-state \
	test.bc 32 

run-klee-dfs: $(TARGET)
	echo "** Running KLEE with dfs search"
	-$(KLEE) \
	--libc=uclibc --posix-runtime \
	--search=dfs \
	test.bc 32

run-klee-coverage: $(TARGET)
	echo "** Running KLEE with coverage search"
	-$(KLEE) \
	--libc=uclibc --posix-runtime \
	--search=nurs:covnew \
	test.bc 32


run-klee-nocfm: $(TARGET)
	echo "** Running KLEE without cfmse"
	-$(KLEE) \
	--max-time=3h -max-memory=32768 -simplify-sym-indices -libc=uclibc --posix-runtime -search=nurs:covnew --only-output-states-covering-new --write-cov \
	--exit-on-error-type=Model \
	--output-dir=klee-nocfm \
	test.bc 40


run-klee-cfmse: $(TARGET)
	echo "** Running KLEE with cfmse search"
	-$(KLEE) \
	--max-time=3h -max-memory=32768 -simplify-sym-indices -libc=uclibc --posix-runtime -search=nurs:covnew --only-output-states-covering-new --write-cov \
	--exit-on-error-type=Model \
	-klee-cfmse  -klee-cfmse-run-only-on-loops=false -klee-cfmse-loads-symbolic \
	--output-dir=klee-cfmse \
	test.bc 40 > run-klee-cfmse.log 2>&1



# all-cse: run-cse-random run-cse-dfs run-cse-coverage

# run-cse-random: $(TARGET)
# 	echo "** Running Chopper with random search"
# 	-$(KLEE) \
# 	--exit-on-error-type=Ptr \
# 	--libc=uclibc --posix-runtime \
# 	$(KSLICE) --search=random-state \
# 	--skip-functions=_asn1_set_value:1043,asn1_der_decoding_bb \
# 	--inline=memcpy,strlen \
# 	--output-dir=cse-run-random \
# 	--no-output \
# 	test.bc 32 > run-cse-random.log 2>&1
# run-cse-dfs: $(TARGET)
# 	echo "** Running Chopper with dfs search"
# 	-$(KLEE) \
# 	--exit-on-error-type=Ptr \
# 	--libc=uclibc --posix-runtime \
# 	$(KSLICE) --search=dfs \
# 	--skip-functions=_asn1_set_value:1043,asn1_der_decoding_bb \
# 	--inline=memcpy,strlen \
# 	--output-dir=cse-run-dfs \
# 	--no-output \
# 	test.bc 32 > run-cse-dfs.log 2>&1
# run-cse-coverage: $(TARGET)
# 	echo "** Running Chopper with coverage search"
# 	-$(KLEE) \
# 	--exit-on-error-type=Ptr \
# 	--libc=uclibc --posix-runtime \
# 	$(KSLICE) --search=nurs:covnew \
# 	--skip-functions=_asn1_set_value:1043,asn1_der_decoding_bb \
# 	--inline=memcpy,strlen \
# 	--output-dir=cse-run-coverage \
# 	--no-output \
# 	test.bc 32 > run-cse-coverage.log 2>&1

clean:
	rm -rf $(DEPS) $(BC_DEPS) $(TARGET)
	rm -f test.*
	rm -rf klee-*
