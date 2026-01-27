ROOT=$(realpath ../..)
include $(ROOT)/case_studies/common.mk

.SILENT:

.PHONY: all
all: bc.bc

.PHONY: clean
clean:
	rm -rf bc-1.06.tar.gz bc-1.06 bc.bc bc_opt.bc

##########################################
#### Case study
##########################################
bc.bc: bc-1.06 bc-1.06/build/Makefile $(WLLVM)
	@echo "Compiling $@"
	cd bc-1.06/build; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM)  $(MAKE) > compilation.log 2>&1; \
	$(EXTRACTBC) bc/bc

bc-1.06.tar.gz:
	@echo "Downloading $@"
	wget -q http://ftp.gnu.org/gnu/bc/bc-1.06.tar.gz

bc-1.06: bc-1.06.tar.gz
	@echo "Decompressing $<"
	tar xfz $<

bc-1.06/build/Makefile: bc-1.06 $(WLLVM)
	@echo "Configuring $@"
	-test -d bc-1.06/build || mkdir -p bc-1.06/build; \
	cd bc-1.06/build; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) ../configure > /dev/null

##########################################
#### Apply optimization on case study
##########################################

bc_opt.bc: bc.bc $(CONDITION_REWRITER_PASS_LIB)
	echo "Run ConditionRewriterPass with OPT on $<"
	$(OPT) -load $(CONDITION_REWRITER_PASS_LIB) $(CONDITION_REWRITER_PASS) $< > $@

##########################################
#### Run KLEE experiments
##########################################
KSEARCH?=dfs
BC_DIR:=$(realpath ./bc-1.06/build)

# Run KLEE on BC given a instruction limit
run-bc: $(KLEE) bc.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program BC"
	-taskset -c 0,1 $(KLEE) --stop-after-n-instructions=53416 \
	--stats-write-interval=0 --istats-write-interval=0 \
	--stats-write-after-instructions=53416 --istats-write-after-instructions=53416 \
	$(KFLAGS) \
	--output-dir=klee-out-bc \
	$(BC_DIR)/bc/bc.bc \
	A --sym-files 1 8 --sym-stdin 8 --sym-stdout \
	> run-klee-$(KSEARCH)-bc.log 2>&1

create-baseline: $(KLEE) bc.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program BC"
	-taskset -c 0,1 $(KLEE) --stats-write-interval=1800 --istats-write-interval=1800 \
	$(KFLAGS) \
	--output-dir=klee-out-bc \
	$(BC_DIR)/bc/bc.bc \
	A --sym-files 1 8 --sym-stdin 8 --sym-stdout \
	> baseline-klee-$(KSEARCH)-bc.log 2>&1
