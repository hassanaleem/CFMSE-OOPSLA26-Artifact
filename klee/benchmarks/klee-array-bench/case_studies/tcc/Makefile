ROOT=$(realpath ../..)
include $(ROOT)/case_studies/common.mk

.SILENT:

.PHONY: all
all: tcc-0.9.26.bc

.PHONY: clean
clean:
	rm -rf tcc-0.9.26* *.log

##########################################
#### Case study
##########################################
tcc-0.9.26.bc: tcc-0.9.26/obj-llvm/Makefile $(WLLVM)
	cd tcc-0.9.26/obj-llvm; \
	$(EXTRACTBC) tcc
	touch $@

tcc-0.9.26.tar.bz2:
	@echo "Downloading $@"
	wget -q http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.26.tar.bz2

tcc-0.9.26: tcc-0.9.26.tar.bz2
	@echo "Decompressing $<"
	tar xfj $<

tcc-0.9.26/obj-llvm/Makefile: tcc-0.9.26 $(WLLVM)
	@echo "Patching lib/libtcc.c"
	patch -p0 < libtcc.patch
	@echo "Compiling $@"
	-test -d tcc-0.9.26/obj-llvm || mkdir -p tcc-0.9.26/obj-llvm; \
	cd tcc-0.9.26/obj-llvm; \
	LLVM_COMPILER=$(LLVM_COMPILER) ../configure CFLAGS="-g -O0" --cc=$(WLLVM) > /dev/null; \
	LLVM_COMPILER=$(LLVM_COMPILER) $(MAKE) CFLAGS="-g -O0" > compilation.log 2>&1
	touch $@

##########################################
#### Run KLEE experiments
##########################################
KSEARCH?=dfs
BC_DIR:=$(realpath ./tcc-0.9.26/obj-llvm)

.PHONY: create-baseline
create-baseline: $(KLEE) tcc-0.9.26.bc
	$(MAKE) prepare
	@echo "Creating baseline for program TinyCC"
	-taskset -c 0,1 $(KLEE) --stats-write-interval=1000 --istats-write-interval=1000 \
	$(KFLAGS) \
	--output-dir=klee-out-tcc \
	$(BC_DIR)/tcc.bc \
	A B C --sym-args 0 3 8 --sym-files 3 800 --sym-stdout \
	> baseline-$(KSEARCH)-klee-tcc.log 2>&1

.PHONY: run-tcc
run-tcc: $(KLEE) tcc-0.9.26.bc
	$(MAKE) prepare
	@echo "Running KLEE on program TinyCC"
	-taskset -c 0,1 $(KLEE) --stop-after-n-instruction=3576284354 \
	--stats-write-after-instructions=119209478 --istats-write-after-instructions=119209478 \
	$(KFLAGS) \
	--output-dir=klee-out-tcc \
	$(BC_DIR)/tcc.bc \
	A B C --sym-args 0 3 8 --sym-files 3 800 --sym-stdout \
	> run-klee-$(KSEARCH)-tcc.log 2>&1
