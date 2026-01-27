ROOT=$(realpath ../..)
include $(ROOT)/case_studies/common.mk

.SILENT:

.PHONY: all
all: SPEC_BUILD

.PHONY: clean
clean:
	rm -rf SPEC_CPU2000v1.3 SPEC_CPU2000v1.3.tar.gz

##########################################
#### Case study
##########################################

SPEC_CPU2000v1.3.tar.gz:
	@echo "Downloading $@"
	wget -q http://web.ics.purdue.edu/~perry74/SPEC_CPU2000v1.3.tar.gz

SPEC_CPU2000v1.3: SPEC_CPU2000v1.3.tar.gz
	@echo "Decompressing $<"
	-test -d $@ || tar xfz $<
	touch $@

.PHONY: SPEC_BUILD
SPEC_BUILD: vpr.bc crafty.bc

vpr.bc: SPEC_CPU2000v1.3
	export LLVM_COMPILER=$(LLVM_COMPILER) && \
	cd SPEC_CPU2000v1.3/benchspec/CINT2000/175.vpr/src/ && \
	sh run.sh && \
	$(EXTRACTBC) vpr && \
	cp vpr.bc ../../../../../

crafty.bc: SPEC_CPU2000v1.3
	export LLVM_COMPILER=$(LLVM_COMPILER) && \
	cd SPEC_CPU2000v1.3/benchspec/CINT2000/186.crafty/src/ && \
	sh run.sh && \
	$(EXTRACTBC) crafty && \
	cp crafty.bc ../../../../../

###########################################
##### Run KLEE experiments
###########################################
KSEARCH?=dfs
BC_DIR:=$(realpath .)

.PHONY: all-dfs
all-dfs:
	$(MAKE) KSEARCH=dfs run-vpr run-crafty

.PHONY: create-baseline
create-baseline:
	$(MAKE) vpr-baseline crafty-baseline

# Run KLEE with a given instruction limit
.PHONY: run-vpr
run-vpr: $(KLEE) vpr.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program vpr"
	-$(KLEE) --stop-after-n-instructions=1000 \
	--stats-write-after-instructions=30 --istats-write-after-instructions=30 \
	$(KFLAGS) \
	--output-dir=klee-out-vpr \
	$(BC_DIR)/vpr.bc A --sym-files 1 8 --sym-stdin 8 --sym-stdout \
	> run-klee-$(KSEARCH)-vpr.log 2>&1

.PHONY: run-crafty
run-crafty: $(KLEE) crafty.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program crafty"
	-$(KLEE) --stop-after-n-instructions=1000 \
	--stats-write-after-instructions=30 --istats-write-after-instructions=30 \
	$(KFLAGS) \
	--output-dir=klee-out-crafty \
	$(BC_DIR)/crafty.bc --sym-stdin 100 --sym-stdout \
	> run-klee-$(KSEARCH)-crafty.log 2>&1

# Run KLEE with a given time limit
.PHONY: vpr-baseline
vpr-baseline: $(KLEE) vpr.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program vpr"
	-$(KLEE) --stats-write-interval=1000 --istats-write-interval=1000 \
	$(KFLAGS) \
	--output-dir=klee-out-vpr \
	$(BC_DIR)/vpr.bc A --sym-files 1 8 --sym-stdin 8 --sym-stdout \
	> baseline-klee-$(KSEARCH)-vpr.log 2>&1

.PHONY: crafty-baseline
crafty-baseline: $(KLEE) crafty.bc prepare
	@echo "Running KLEE with $(KSEARCH) on program crafty"
	-$(KLEE) --stats-write-interval=1000 --istats-write-interval=1000 \
	$(KFLAGS) \
	--output-dir=klee-out-crafty \
	$(BC_DIR)/crafty.bc --sym-stdin 100 --sym-stdout \
	> baseline-klee-$(KSEARCH)-crafty.log 2>&1

## Create both the enviroment file and the sandbox directory
.PHONY: prepare
prepare: testing-env.sh sandbox.tgz
	-rm -rf /tmp/*
	env -i /bin/bash -c '(source testing-env.sh; env >test.env)'; \
	mv test.env /tmp/test.env
	tar xzf sandbox.tgz; \
	mv sandbox /tmp

sandbox.tgz:
	wget -q http://www.doc.ic.ac.uk/~cristic/klee/sandbox.tgz
