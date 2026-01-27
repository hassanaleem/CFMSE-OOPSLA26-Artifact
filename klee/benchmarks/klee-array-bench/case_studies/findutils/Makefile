ROOT=$(realpath ../..)
include $(ROOT)/case_studies/common.mk

.SILENT:

.PHONY: all
all: findutils-4.6.0.bc

.PHONY: clean
clean:
	rm -rf findutils-4.6.0* *.log

##########################################
#### Case study
##########################################
findutils-4.6.0.bc: findutils-4.6.0 findutils-4.6.0/obj-llvm/Makefile $(WLLVM)
	cd findutils-4.6.0/obj-llvm; \
	for exe in `find find -executable -type f`; do \
		$(EXTRACTBC) $$exe; \
	done; \
	for exe in `find locate -executable -type f`; do \
		$(EXTRACTBC) $$exe; \
	done
	touch $@

findutils-4.6.0.tar.gz:
	@echo "Downloading $@"
	wget -q https://ftp.gnu.org/gnu/findutils/findutils-4.6.0.tar.gz

findutils-4.6.0: findutils-4.6.0.tar.gz
	@echo "Decompressing $<"
	tar xfz $<

findutils-4.6.0/obj-llvm/Makefile: findutils-4.6.0 $(WLLVM)
	@echo "Compiling $@"
	-test -d findutils-4.6.0/obj-llvm || mkdir -p findutils-4.6.0/obj-llvm; \
	cd findutils-4.6.0/obj-llvm; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) ../configure --disable-nls CFLAGS="-g" > /dev/null; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) $(MAKE) > compilation.log 2>&1

##########################################
#### Run KLEE experiments
##########################################
KSEARCH?=dfs
BC_DIR:=$(realpath ./findutils-4.6.0/obj-llvm)

## TARGETS contains all target programs in targets.txt in the format PROGRAM:DFS_INSTR_LIMIT:BFS_INSTR_LIMIT
TARGETS=$(shell test -r targets.txt && cat targets.txt)

.PHONY: all-dfs all-bfs
all-dfs: findutils-4.6.0.bc
	$(MAKE) $(foreach line,$(TARGETS),run-klee-$(firstword $(subst :, ,$(line)))_$(word 2,$(subst :, ,$(line)))_$(word 3,$(subst :, ,$(line))))
all-bfs: findutils-4.6.0.bc
	$(MAKE) $(foreach line,$(TARGETS),run-klee-$(firstword $(subst :, ,$(line)))_$(word 4,$(subst :, ,$(line)))_$(word 5,$(subst :, ,$(line))))

## This target runs all the experiments by using Make macros to create the baseline (i.e. to extract # of instructions)
.PHONY: create-baseline
create-baseline: findutils-4.6.0.bc
	$(MAKE) $(foreach line,$(TARGETS),baseline-klee-$(firstword $(subst :, ,$(line))))

run-klee-find_$(2)_$(3): $(KLEE)
	$(MAKE) prepare
	@echo "Running KLEE with $(KSEARCH) on program find"
	-taskset -c 0,1 $(KLEE) --stop-after-n-instructions=$(2) \
	--stats-write-interval=0 --istats-write-interval=0 \
	--stats-write-after-instructions=$(3) --istats-write-after-instructions=$(3) \
	$(KFLAGS) \
	--output-dir=klee-out-find \
	$(BC_DIR)/find/find.bc \
	--sym-args 0 1 10 --sym-args 1 10 300 --sym-files 3 8 --sym-stdin 8 --sym-stdout \
	> run-klee-$(KSEARCH)-find_$(2)_$(3).log 2>&1

run-klee-locate_$(2)_$(3): $(KLEE)
	$(MAKE) prepare
	@echo "Running KLEE with $(KSEARCH) on program locate"
	-taskset -c 0,1 $(KLEE) --stop-after-n-instructions=$(2) \
	--stats-write-interval=0 --istats-write-interval=0 \
	--stats-write-after-instructions=$(3) --istats-write-after-instructions=$(3) \
	$(KFLAGS) \
	--output-dir=klee-out-locate \
	$(BC_DIR)/locate/locate.bc \
	--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 30 --sym-stdin 30 --sym-stdout \
	> run-klee-$(KSEARCH)-locate_$(2)_$(3).log 2>&1

baseline-klee-find: $(KLEE)
	$(MAKE) prepare
	@echo "Creating KLEE baseline with $(KSEARCH) on program find"
	-taskset -c 0,1 $(KLEE) --stats-write-interval=1500 --istats-write-interval=1500 \
	$(KFLAGS) \
	--output-dir=klee-out-find \
	$(BC_DIR)/find/find.bc \
	--sym-args 0 1 10 --sym-args 1 10 300 --sym-files 3 8 --sym-stdin 8 --sym-stdout \
	> baseline-klee-$(KSEARCH)-find.log 2>&1

baseline-klee-locate: $(KLEE)
	$(MAKE) prepare
	@echo "Creating KLEE baseline with $(KSEARCH) on program locate"
	-taskset -c 0,1 $(KLEE) --stats-write-interval=1500 --istats-write-interval=1500 \
	$(KFLAGS) \
	--output-dir=klee-out-locate \
	$(BC_DIR)/locate/locate.bc \
	--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 30 --sym-stdin 30 --sym-stdout \
	> baseline-klee-$(KSEARCH)-locate.log 2>&1
