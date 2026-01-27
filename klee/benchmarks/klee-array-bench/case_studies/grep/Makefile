ROOT=$(realpath ../..)
include $(ROOT)/case_studies/common.mk

.SILENT:

.PHONY: all
all: idutils-4.6.bc

.PHONY: clean
clean:
	rm -rf idutils-4.6* *.log

##########################################
#### Case study
##########################################
grep-2.27.bc: grep-2.27 grep-2.27/obj-llvm/Makefile $(WLLVM)
	cd grep-2.27/obj-llvm/src; \
	for exe in `find . -executable -type f`; do \
		$(EXTRACTBC) $$exe; \
	done; \
	touch $@

grep-2.27.tar.xz:
	@echo "Downloading $@"
	wget -q http://ftp.gnu.org/gnu/grep/grep-2.27.tar.xz

grep-2.27: grep-2.27.tar.xz
	@echo "Decompressing $<"
	tar xfJ $<

grep-2.27/obj-llvm/Makefile: grep-2.27 $(WLLVM)
	@echo "Compiling $@"
	-test -d grep-2.27/obj-llvm || mkdir -p grep-2.27/obj-llvm; \
	cd grep-2.27/obj-llvm; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) ../configure --disable-nls CFLAGS="-g" > /dev/null; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) $(MAKE) > compilation.log 2>&1

##########################################
#### Run KLEE experiments
##########################################
KSEARCH?=dfs
BC_DIR:=$(realpath ./grep-2.27/obj-llvm/src)

## This target runs all the experiments by using Make macros to create the baseline (i.e. to extract # of instructions)
.PHONY: create-baseline
create-baseline: grep-2.27.bc
	$(MAKE) prepare
	@echo "Creating KLEE baseline with $(KSEARCH) on program grep"
	-taskset -c 0,1 $(KLEE) --stats-write-interval=1500 --istats-write-interval=1500 \
	$(KFLAGS) \
	--output-dir=klee-out-grep \
	$(BC_DIR)/grep.bc \
	--sym-args 0 1 10 --sym-args 1 2 300 --sym-files 2 30 --sym-stdin 30 --sym-stdout \
	> baseline-klee-$(KSEARCH)-grep.log 2>&1

run-klee-grep: $(KLEE)
	$(MAKE) prepare
	@echo "Running KLEE with $(KSEARCH) on program grep"
	-taskset -c 0,1 $(KLEE) --stop-after-n-instructions=40000 \
	--stats-write-interval=0 --istats-write-interval=0 \
	--stats-write-after-instructions=30000 --istats-write-after-instructions=30000 \
	$(KFLAGS) \
	--output-dir=klee-out-grep \
	$(BC_DIR)/grep.bc \
	--sym-args 0 1 10 --sym-args 1 2 300 --sym-files 2 30 --sym-stdin 30 --sym-stdout \
	> run-klee-$(KSEARCH)-grep.log 2>&1
