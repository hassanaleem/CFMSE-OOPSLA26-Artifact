include ../common.mk

SRC_PATH=./yaml-0.1.5

INCLUDES=-I $(KLEE_SRC_DIR)/include -I $(SRC_PATH)/include -I $(SRC_PATH)
DEFINES=-D_GNU_SOURCE -DHAVE_CONFIG_H

CFLAGS=-emit-llvm -c -g $(DEFINES) $(INCLUDES)
LDFLAGS=-lgcov --coverage
CC=gcc

%.o: %.c
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $< -o $@

%.bc: %.c
	$(CLANG) $(CFLAGS) -DTEST_SYMBOLIC $< -o $@

SOURCES=$(shell ls $(SRC_PATH)/src/*.c) main.c
DEPS=$(patsubst %.c,%.o,$(SOURCES))
BC_DEPS=$(patsubst %.c,%.bc,$(SOURCES))
BC_TARGET=test-driver.bc
TARGET=test-driver-gcov

$(BC_TARGET): $(BC_DEPS)
	$(LINK) $^ -o $@
	$(OPT) -mem2reg $@ -o $@
	$(DIS) $@

$(TARGET): $(DEPS)
	$(CC) $^ -o $@ $(LDFLAGS) 

all: $(BC_TARGET)

clean:
	rm -rf $(BC_DEPS) $(DEPS) $(BC_TARGET) $(TARGET) *.bc *.ll *.gcno
