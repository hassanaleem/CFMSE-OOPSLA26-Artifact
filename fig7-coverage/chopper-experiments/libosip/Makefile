include ../common.mk

SRC_PATH=./libosip2-4.0.0/

INCLUDES=-I $(KLEE_SRC_DIR)/include -I $(SRC_PATH)/include
DEFINES=

COVERAGE_CFLAGS=-fprofile-arcs -ftest-coverage
COVERAGE_LDFLAGS=-lgcov --coverage

CFLAGS=$(INCLUDES) $(DEFINES) -g
LDFLAGS=
CC=gcc

TARGET=test-driver
TARGET_GCOV=test-driver-gcov
BC_TARGET=test-driver.bc

%.o: %.c
	LLVM_COMPILER_PATH=$(LLVM_BUILD_DIR) LLVM_COMPILER=clang $(WLLVM) -c $(CFLAGS) -DTEST_SYMBOLIC $< -o $@

%.gcov.o: %.c
	$(CC) -c $(CFLAGS) $(COVERAGE_CFLAGS) $< -o $@

.PHONY: osip_archive osip_archive_gcov

osip_archive_gcov:
	rm -rf build && mkdir build
	cd build; ../libosip2-4.0.0/configure CFLAGS="$(COVERAGE_CFLAGS)" LDFLAGS="$(COVERAGE_LDFLAGS)"; cd -
	make -C build -j4

osip_archive:
	rm -rf build && mkdir build
	cd build; LLVM_COMPILER_PATH=$(LLVM_BUILD_DIR) LLVM_COMPILER=clang ../libosip2-4.0.0/configure CC=$(WLLVM)
	LLVM_COMPILER_PATH=$(LLVM_BUILD_DIR) LLVM_COMPILER=clang make -C build -j4

$(TARGET_GCOV): main.gcov.o osip_archive_gcov
	$(CC) $(CFLAGS) $(LDFLAGS) $(COVERAGE_CFLAGS) $(COVERAGE_LDFLAGS) $< ./build/src/osipparser2/.libs/libosipparser2.a -o $@

$(TARGET): main.o osip_archive
	LLVM_COMPILER_PATH=$(LLVM_BUILD_DIR) LLVM_COMPILER=clang $(WLLVM) $(CFLAGS) $(LDFLAGS) $< ./build/src/osipparser2/.libs/libosipparser2.a -o $@

$(BC_TARGET): $(TARGET) osip_archive
	LLVM_COMPILER_PATH=$(LLVM_BUILD_DIR) LLVM_COMPILER=clang $(EXTRACTBC) $< -o $@
	$(OPT) -mem2reg $@ -o $@

clean:
	rm -rf $(TARGET) $(TARGET_GCOV) $(BC_TARGET) *.o *.bc *.ll ./klee-* ./build
