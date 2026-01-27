ROOT=$(realpath ../..)
include $(ROOT)/case_studies/common.mk

.SILENT:

.PHONY: all
all: bandicoot-v6.bc

.PHONY: clean
clean:
	rm -rf bandicoot-v6* *.log

##########################################
#### Case study
##########################################
bandicoot-v6.bc: bandicoot-v6 bandicoot-v6/bin/bandicoot $(WLLVM)
	cd bandicoot-v6/bin; \
	$(EXTRACTBC) bandicoot
	touch $@

bandicoot-v6: 
	@echo "Downloading $@"
	git clone --branch v6 https://github.com/bandilab/bandicoot.git $@

bandicoot-v6/bin/bandicoot: bandicoot-v6 $(WLLVM)
	@echo "Patching language.l"
	patch -p0 < language.patch
	@echo "Patching CTL"
	sed -i 's/CC=\"gcc/CC=\"$(subst /,\/,$(WLLVM))/g' bandicoot-v6/ctl
	@echo "Compiling $@"
	cd bandicoot-v6; \
	LLVM_COMPILER=$(LLVM_COMPILER) CC=$(WLLVM) ./ctl pack > compilation.log 2>&1

##########################################
#### Run KLEE experiments
##########################################
KSEARCH?=dfs
BC_DIR:=$(realpath ./bandicoot-v6/bin)

# Run KLEE on BANDICOOT given a instruction limit
run-bandicoot: $(KLEE) bandicoot-v6.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program BANDICOOT"
	-taskset -c 0,1 $(KLEE) --stop-after-n-instruction=1000 \
	--stats-write-after-instructions=30 --istats-write-after-instructions=30 \
	$(KFLAGS) \
	--output-dir=klee-out-bandicoot \
	$(BC_DIR)/bandicoot.bc \
	--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 30 --sym-stdin 30 --sym-stdout \
	> run-klee-$(KSEARCH)-bandicoot.log 2>&1

create-baseline: $(KLEE) bandicoot-v6.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program BANDICOOT"
	-taskset -c 0,1 $(KLEE) --stats-write-interval=1500 --istats-write-interval=1500 \
	$(KFLAGS) \
	--output-dir=klee-out-bandicoot \
	$(BC_DIR)/bandicoot.bc \
	--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 30 --sym-stdin 30 --sym-stdout \
	> baseline-klee-$(KSEARCH)-bandicoot.log 2>&1

