ROOT=$(realpath ../..)
include $(ROOT)/case_studies/common.mk

.SILENT:

.PHONY: all
all: coreutils-6.11.bc

.PHONY: clean
clean:
	rm -rf coreutils-6.11* *.log

##########################################
#### Case study
##########################################
coreutils-6.11.bc: coreutils-6.11 coreutils-6.11/obj-llvm/Makefile $(WLLVM)
	cd coreutils-6.11/obj-llvm/src; \
	for exe in `find . -executable -type f`; do \
		$(EXTRACTBC) $$exe; \
	done
	touch $@

coreutils-6.11.tar.gz:
	@echo "Downloading $@"
	wget -q http://ftp.gnu.org/gnu/coreutils/coreutils-6.11.tar.gz

coreutils-6.11: coreutils-6.11.tar.gz
	@echo "Decompressing $<"
	tar xfz $<

coreutils-6.11/obj-llvm/Makefile: coreutils-6.11 $(WLLVM)
	@echo "Compiling $@"
	-test -d coreutils-6.11/obj-llvm || mkdir -p coreutils-6.11/obj-llvm; \
	cd coreutils-6.11/obj-llvm; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) ../configure --disable-nls CFLAGS="-g" > /dev/null; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) $(MAKE) > compilation.log 2>&1; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) $(MAKE) -C src arch hostname >> compilation.log 2>> compilation.log

##########################################
#### Run KLEE experiments
##########################################
KSEARCH?=dfs
BC_DIR:=$(realpath ./coreutils-6.11/obj-llvm/src)

## TARGETS contains all target programs in targets.txt in the format PROGRAM:DFS_INSTR_LIMIT:BFS_INSTR_LIMIT
TARGETS=$(shell test -r targets.txt && cat targets.txt)

.PHONY: all-dfs all-bfs
all-dfs: coreutils-6.11.bc
	$(MAKE) $(foreach line,$(TARGETS),run-klee-$(firstword $(subst :, ,$(line)))_$(word 2,$(subst :, ,$(line)))_$(word 3,$(subst :, ,$(line))))
all-bfs: coreutils-6.11.bc
	$(MAKE) $(foreach line,$(TARGETS),run-klee-$(firstword $(subst :, ,$(line)))_$(word 4,$(subst :, ,$(line)))_$(word 5,$(subst :, ,$(line))))

## This target runs all the experiments by using Make macros to create the baseline (i.e. to extract # of instructions)
.PHONY: create-baseline
create-baseline: coreutils-6.11.bc
	$(MAKE) $(foreach line,$(TARGETS),baseline-klee-$(firstword $(subst :, ,$(line))))

## Here we define the basic macro expansion
define run_program
 run-klee-$(1)_$(2)_$(3): $(KLEE)
	$(MAKE) prepare
	@echo "Running KLEE with $(KSEARCH) on program $(1)"
	-$(KLEE) --stop-after-n-instructions=$(2) \
	--stats-write-interval=0 --istats-write-interval=0 \
	--stats-write-after-instructions=$(3) --istats-write-after-instructions=$(3) \
	$(KFLAGS) \
	--output-dir=klee-out-$(1) \
	$(BC_DIR)/$(1).bc \
	--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 --sym-stdin 8 --sym-stdout \
	> run-klee-$(KSEARCH)-$(1)_$(2)_$(3).log 2>&1
endef

## This is the "expansion" for the macro defined above.
$(foreach line,$(TARGETS),$(eval $(call run_program,$(firstword $(subst :, ,$(line))),$(word 2,$(subst :, ,$(line))),$(word 3,$(subst :, ,$(line))))))
$(foreach line,$(TARGETS),$(eval $(call run_program,$(firstword $(subst :, ,$(line))),$(word 4,$(subst :, ,$(line))),$(word 5,$(subst :, ,$(line))))))

## Here we define the macro expansion for creating the baseline
define baseline_program
 baseline-klee-$(1): $(KLEE)
	$(MAKE) prepare
	@echo "Creating KLEE baseline with $(KSEARCH) on program $(1)"
	-$(KLEE) --stats-write-interval=1500 --istats-write-interval=1500 \
	$(KFLAGS) \
	--output-dir=klee-out-$(1) \
	$(BC_DIR)/$(1).bc \
	--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 --sym-stdin 8 --sym-stdout \
	> baseline-klee-$(KSEARCH)-$(1).log 2>&1
endef

## This is the "expansion" for the macro defined above.
$(foreach line,$(TARGETS),$(eval $(call baseline_program,$(firstword $(subst :, ,$(line))))))

## Including specials to override expanded macros
include Makefile.specials
