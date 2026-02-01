## Overview
This artifact supports the experiment results shown in the paper, including coverage measurements, bug detection results, small benchmark evaluations, and scalability experiments. The artifact includes an implementation of the proposed transformation, benchmark programs, and evaluation scripts necessary to produce the results.

**Note:** The configurations provided in this artifact are designed for a machine with more than **164 GB RAM**, but can be easily adapted to systems with lower memory. We provide details in the [Evaluation](#evaluation-and-expected-results) section on the changes required in the configuration to prevent system crashes.


## Artifact Checklist
* **LLVM version**: LLVM 14.0.0.
* **Compilation**: CMake with LLVM build system.
* **Run-time environment**: Linux operating system.
* **Hardware**: No specific hardware requirements. We have tested our approach on Intel(R) Xeon(R) Gold 6430 (64 cores) processor and 256 GB RAM.
* **Metrics**: Coverage, runtime speedup, number of queries, query size, and explored path count.
* **Output**: Optimized LLVM IR, binaries, raw logs.
* **Experiment Workflow**: Download source code and benchmarks, compile the source code or build the Dockerfile, run the scripts to generate the results.
* **Disk space required**: No additional disk space required beyond standard LLVM build.
* **Publicly available**: Will be made available after the evaluation.
* **Workflow automation**: Bash and Python scripts.


## Dependencies
This artifact is packaged as a Docker image and requires no manual dependency installation beyond Docker itself. All software dependencies are installed automatically upon building the container from the provided Dockerfile. No additional system libraries, tools, or external services are required on the host machine

## Installation

**Warning** Building the image may take from a few minutes on a 128-core machine up to an hour on smaller machines, as LLVM and KLEE are built from source.

By default, this build uses 4 cores to avoid out-of-memory failures. On systems with sufficient memory and CPU resources, build time can be reduced by replacing `-j4` in the Dockerfile with  `-j\$(nproc)`.

To build the Docker image:

```bash
docker build -t cfmse .
```

To start an interactive container and mount the artifact directory:
```bash
docker run -it -v "$(pwd):/artifact" --name cfmse-session --memory 220g --memory-swap 240g cfmse
```

We recommend this memory configuration for a system with ~256 GB memory, used for all our experiments. For a system with lower memory, adjust the values accordingly. 

The container can be stopped and restarted later without rebuilding the image:
```bash
docker start cfmse-session
docker exec -it cfmse-session bash
```

## Kick The Tires
To verify that the artifact is functioning correctly, we provide a small test script. Navigate to the `KickTheTires` directory in the artifact and run the provided `runme` script. This script applies the CFMSE transformation and runs KLEE on the `ToUpper` function and produces a CSV file named `toupper.csv`.

We include a `reference-toupper.csv` file in the directory to allow comparison with a reference. The results may not be identical across systems, but should remain qualitatively consistent. 

If the generated file contains non-zero values, the artifact is working as expected. Some fields in the CSV may contain `OOT`, which is expected and indicates KLEE has hit a timeout (60s) for this particular analysis. This script takes approximately 3 minutes to complete. Once this check succeeds, you may proceed to the remaining experiments.

## Building From Scratch
These build instructions were tested on `Ubuntu 24.04`. 
If you installed the artifact using the provided Dockerfile as described in the previous section, all dependencies are already installed, and the artifact is already built, so you may skip to the next section. 
However, if you wish to build the artifact from scratch, follow the instructions below. 

By default, these instructions use 4 cores to avoid out-of-memory failures. On systems with sufficient memory and CPU resources, build time can be reduced by replacing `-j4` with `-j\$(nproc)`.

### 1 install all system dependencies

```bash
# 0) enter artifact directory
cd <ARTIFACT>

sudo apt-get update
sudo apt-get install -y \
  build-essential cmake bison flex libboost-all-dev perl zlib1g-dev minisat \
  ninja-build git wget curl python3 python-is-python3 \
  libncurses5-dev libncursesw5-dev \
  libgoogle-perftools-dev libsqlite3-dev \
  gperf pkg-config libprotobuf-dev protobuf-compiler libprotoc-dev

pip3 install setuptools \
  tabulate pandas matplotlib psutil  wllvm
```

### 2 Building STP
```bash
cd stp
mkdir -p build
cd build
cmake ..
make
sudo make install
cd ../..
```
### 3 Building LLVM and CFMSE
```bash
cd llvm-project-cfmse
cmake -G Ninja -B build_cfmse -S llvm \
  -DLLVM_ENABLE_PROJECTS="clang" \
  -DLLVM_BUILD_EXAMPLES=ON \
  -DLLVM_TARGETS_TO_BUILD="X86" \
  -DCMAKE_BUILD_TYPE=Release \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DCMAKE_CXX_COMPILER=g++ \
  -DLLVM_USE_LINKER=gold \
  -DCMAKE_INSTALL_PREFIX="$(pwd)/install"

ninja -C build_cfmse
ninja -C build_cfmse install
cd ..
```

### 4 Setting LLVM environment variables
```bash
export EXPERIMENT_HOME="$(pwd)"
export LLVM_BUILD_DIR="${EXPERIMENT_HOME}/llvm-project-cfmse/build_cfmse"
export CLANG="${LLVM_BUILD_DIR}/bin/clang"
export OPT="${LLVM_BUILD_DIR}/bin/opt"
```
### 5 Building klee-uclibc
```bash
cd klee-uclibc
./configure --make-llvm-lib \
  --with-cc "${LLVM_BUILD_DIR}/bin/clang" \
  --with-llvm-config "${LLVM_BUILD_DIR}/bin/llvm-config"
make -j4
cd ..
```

### 6 Building KLEE
```bash
cd klee
mkdir -p build
cd build
cmake -DENABLE_SOLVER_STP=ON \
  -DENABLE_POSIX_RUNTIME=ON \
  -DENABLE_KLEE_UCLIBC=ON \
  -DKLEE_UCLIBC_PATH="${EXPERIMENT_HOME}/klee-uclibc/" \
  -DLLVM_CONFIG_BINARY="${LLVM_BUILD_DIR}/bin/llvm-config" \
  -DLLVMCC="${LLVM_BUILD_DIR}/bin/clang" \
  -DLLVMCXX="${LLVM_BUILD_DIR}/bin/clang++" \
  ..
make -j4
cd ../..
```

### 7 Setting KLEE paths
```bash
export KLEE_BUILD_DIR="${EXPERIMENT_HOME}/klee/build"
export KLEE="${KLEE_BUILD_DIR}/bin/klee"
export KTEST_TOOL="${KLEE_BUILD_DIR}/bin/ktest-tool"
export KLEE_INCLUDE="${EXPERIMENT_HOME}/klee/include"
export KLEE_STATS="${KLEE_BUILD_DIR}/bin/klee-stats"
```

## Experiment Workflow
The files and configurations necessary to reduce the results are organized by table or figure number. For example, to reproduce the results in **Figure 7 (Coverage)**, navigate to the `fig7-coverage` folder within the artifact directory. This directory contains a runme script that can be executed to generate all the corresponding coverage plots.

Alternatively, users may navigate to specific directories and run individual `run-cfm-driver` scripts. Configuration options for each program can be found within the `driver_options.json` file in the program's directory.

The configuration file defines two sets of options. The first includes standard KLEE flags that control symbolic execution behaviour within KLEE, such as search heuristics, runtime and memory limits, etc. The second set contains CFM-specific options, allowing users to enable CFMSE for symbolic branches, force CFMSE on all branches or restrict branch merging to loops only.

These configurations can be modified to provide flexibility to evaluate different program variants and experiments under controlled memory and runtime conditions for different machines.

To modify the timeout for KLEE, adjust the `max-time` flag in `KLEE_OPTIONS`. To change the maximum memory limit, modify the `max-memory` flag.

To control the applicability of CFMSE, modify the options in `CFM_OPTIONS`:
* The `klee-cfmse` flag enables the CFMSE transformation, which by default applies only to symbolic branches.
* To apply to all branches, add the `klee-force-cfmse` flag.
* To restrict CFMSE to loops only, set the flag `klee-cfmse-run-only-on-loops` to true.
* To treat the loads as symbolic, use the flag `klee-cfmse-loads-symbolic`.

`PROG_ARGS` specifies the command line arguments passed to the target program. Some programs in our benchmarks require parameters such as input or buffer size. When present, this usually corresponds to the size of the symbolic array in the target program.

We recommend using the following configuration:
```json
{
  "KLEE_OPTIONS" : "--max-time=3h -max-memory=32768 -simplify-sym-indices -libc=uclibc -search=nurs:covnew --only-output-states-covering-new --write-cov",
  "CFMSE_IGNORE_JSON" : "cfmse_ignore.json",
  "CFM_OPTIONS" : "-klee-cfmse  -klee-cfmse-run-only-on-loops=false -klee-cfmse-loads-symbolic",
  "PROG_ARGS" : "  "
}
```

To execute on machines with memory lower than 160GB, navigate to each benchmark program directory and modify the `driver_options.json` based on your system specifications to avoid potential system crashes. For **Table 3** modify the `makefile.in` instead of `driver_options.json`. Ensure that the `max-memory` is set below the total memory available to your system for all experiments. Additionally, configure Docker memory to avoid system crashes as described in the Installation Section.


## Evaluation and expected results
To generate the table in **Table 3** run the following commands. 

```bash
cd table3-small-benchmarks
./runme.sh

# To run an individal benchmark
./run-bench-<benchmark>.sh
```

The total runtime depends on the benchmark being executed. Approximate execution times (per benchmark) are as follows:

* `toupper`: 10 hours
* `bitonic sort`: 10 hours
* `connected components`: 10 hours
* `prim`: 10 hours
* `merge sort`: 40 hours
* `transitive closure`: 6 hours
* `detect edges`: 15 hours
* `floyd warshall`: 15 hours
* `erosion`: 6 hours
* `dijkstra`: 10 hours
* `total time`: 132 hours



### Timeout and repetitions
Each benchmark is executed with a timeout of 1 hour and repeated for 5 runs. To reduce the number of repetitions, navigate to the corresponding script
`run-bench-<benchmark>.sh` and modify the third argument of the `run_bench` invocation. For example:

```bash
run_bench "bitonic_sort" "4 8 16" "5" "klee_cfm"
```
Replace **5** with the desired number of runs.

### Adjusting the timeout
To reduce the timeout value, edit `makefile.in` and change the  max-time` flag to the desired duration. Note that modifying the timeout or the number of runs may affect the total number of generated queries.

For the CFMSE transformation, only the **merge sort** benchmark reaches the timeout limit. All other benchmarks complete within one minute.

To generate plots from **Figure 6** run the following commands. 


```bash
cd fig6-completed-paths-merge-sort
./runme.sh
```
This takes approximately 30 hours to run.

To generate plots from **Figure 7** run the following commands.

```bash 
cd fig7-coverage
./runme.sh
# To run individual experiments
cd <benchmark directory>
./run-cfm-driver.sh
```
This script takes approximately 16 hours to run. 
* `Libosip`: 3 hours
* `Libyaml`: 3 hours
* `libtasn`: 1 minute
* `chcon`: 1 hour
* `chown`: 1 hour
* `mkdir`: 1 hour
* `mkfifo`: 1 hour
* `json.h`: 3 hours
* `protobuf`: 1 hour
* `utf8-valud`: 1 hour
* `utf8-nonvaid`: 30 minutes
* `total`: 16 hours

To generate plots from **Figure 10 and 11** run the following commands.

```bash
cd fig10-11-bug-detection-and-killed-states
./runme.sh

# To run individual experiments
cd <benchmark> directory
./run.sh
```

This script takes approximately 158 hours (6.5 days) to run.
* `Tiny-regex-c`: 1 hour
* `utf8`: 1 hour
* `json.h`: 1 hour
* `libosip`: 72 hours
* `libyaml`: 21 hours
* `total`: 96 hours

Plots for **Figure 11** depend on the results of Libyaml and Libosip. The framework will auto generate them.

Table 4 relies on the previous experiments being run and can not be run standalone. To generate the table in **Table 4** first run all previous experiments, then run the following commands.

```bash
cd table4-overhead
./runme.sh
```

After successfully executing the `runme` script, the framework will generate the corresponding plots or tables. These outputs should closely match the results presented in the paper. Minor variations may occur due to differences in hardware architecture and nondeterminism in KLEE's execution. 

In addition to the plots and tables, the framework also generates a detailed execution log, as well as a transformed intermediate representation (IR) file. The log file reports summary statistics related to the CFMSE transformation, including the number of CFMSE applications and the number of select conversions achieved by the CFMSE transformation. The listing below shows a snippet of the execution log for `tiny-regex-c`. The complete log file contains a complete execution trace of KLEE and the CFM driver, reporting all detected false-positive bugs as well as the true-positive bug.

**Excerpt from execution log of Tiny-Regex-C:**
```log
INFO[cfmse]: Running CFMSE ...
INFO[cfmse]: Select Instructions before CFMSE : 3
INFO[cfmse]: Cond Branch Instructions before CFMSE : 183
INFO[cfmse]: Uncond Branch Instructions before CFMSE : 239
INFO[cfmse]: Total Instructions before CFMSE : 3877
INFO[cfmse]: Number of successful applications of CFMSE : 13
INFO[cfmse]: Number of if-then merges : 12
INFO[cfmse]: Number of if-then-else merges : 1
INFO[cfmse]: Number of select instructions added : 13
INFO[cfmse]: Select Instructions after CFMSE : 16
INFO[cfmse]: Cond Branch Instructions after CFMSE : 170
INFO[cfmse]: Uncond Branch Instructions after CFMSE : 238
INFO[cfmse]: Total Instructions after CFMSE : 3707
CFMSE took 1.000000e-02 ms.
```

## Experiment Customization and Reusability

We now discuss how the proposed transformation can be extended to programs beyond those considered in this study. Since our approach is implemented as an LLVM transformation, it can be applied to any program that can be compiled into LLVM bitcode.

We present this process in two parts. First, we describe how to apply the transformation as a standalone LLVM pass. Second, we explain how to use the transformed program within the KLEE-based test driver.

### Standalone LLVM Transformation.
Let us consider a program `tutorial.c`. To compile this program into LLVM bitcode, we use the following command:

```bash
$CLANG -c -emit-llvm -Xclang -disable-O0-optnone -O0 tutorial.c -o tutorial.bc
```
Once the LLVM bitcode is generated, we apply the CFMSE transformation using `opt`:

```bash
$OPT -f -cfmse tutorial.bc -o tutorial-cfmse.bc
```

By default, this transformation applies only to symbolic branches in the program. However, we can force the transformation to  be applied to all branches by using the `-force-cfmse` flag:

```bash
$OPT -f -cfmse -force-cfmse tutorial.bc -o tutorial-cfmse.bc
```

Here, `$CLANG` and `$OPT` refer to the paths of the `clang` and `opt` binaries, respectively, as defined in our Dockerfile.

### Using the Transformation with KLEE
To use the transformed program with the test driver, we first compile the target program into LLVM bitcode, as described above. We then define a configuration file, `driver_options.json`, which specifies the options passed to KLEE and the CFMSE extension.

A sample configuration file is shown below and can be used without modification:

```json
{
  "KLEE_OPTIONS" : "--max-time=86400s -max-memory=51200",
  "CFMSE_IGNORE_JSON" : "cfmse_ignore.json",
  "CFM_OPTIONS" : "-klee-cfmse -klee-cfmse-run-only-on-loops=false",
  "PROG_ARGS" : ""
}
```

Additional KLEE flags may be introduced by modifying the `KLEE_OPTIONS` field.

Finally, we run the test driver using the following command:

```python
python3 ${KLEE_BUILD_DIR}/../scripts/cfm_driver/driver.py -e -i ./test-driver.bc -k driver_options.json -r $main_dir/$benchName
```

In this command, the user provides the input LLVM bitcode file, the JSON configuration file containing the driver options, and the output directory where the results are stored.

The driver executes KLEE on the provided program and terminates as soon as the first true positive bug is discovered.

Since CFMSE is implemented as LLVM transformation, it resides within the LLVM framework. Thus, for this artifact, we modify both the LLVM and KLEE source code. Our LLVM changes can be found inside `llvm/lib/Transforms/CFMSE`. Since we now need to call this transformation from within KLEE, we modify its source by adding a call to our transformation in the `KModule.cpp` file present in `klee/lib/Module`. 