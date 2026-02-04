
FROM ubuntu:24.04

# Set a working directory inside the container. All subsequent commands will run from here.
WORKDIR /cfmse

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    bison flex libboost-all-dev python3 perl zlib1g-dev minisat \
    ninja-build \
    git \
    python3-tabulate \
    python3-pandas \
    python3-matplotlib \
    python-is-python3 \
    python3-setuptools \
    libncurses5-dev \
    libncursesw5-dev \
    wget \
    curl \
    && rm -rf /var/lib/apt/lists/*

COPY llvm-project-cfmse /cfmse/llvm-project-cfmse
COPY klee /cfmse/klee
COPY klee-uclibc /cfmse/klee-uclibc
COPY stp /cfmse/stp

RUN find . \
    -type f \
    \( \
    -name "*.sh" \
    -o -name "configure" \
    -o -name "klee-stats" \
    \) \
    -exec chmod +x {} +


RUN cd stp && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install


RUN cd llvm-project-cfmse && \ 
    cmake -G Ninja -B build_cfmse -S llvm \
    -DLLVM_ENABLE_PROJECTS="clang" \
    -DLLVM_BUILD_EXAMPLES=ON \
    -DLLVM_TARGETS_TO_BUILD="X86" \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DCMAKE_CXX_COMPILER=g++ \
    -DLLVM_USE_LINKER=gold \
    -DCMAKE_INSTALL_PREFIX=/cfmse/llvm-project-cfmse/install && \
    ninja -C build_cfmse -j4 && \
    ninja -C build_cfmse install



ENV EXPERIMENT_HOME /cfmse
ENV LLVM_BUILD_DIR ${EXPERIMENT_HOME}/llvm-project-cfmse/build_cfmse
ENV CLANG ${LLVM_BUILD_DIR}/bin/clang
ENV OPT ${LLVM_BUILD_DIR}/bin/opt


RUN cd klee-uclibc && \
    ./configure --make-llvm-lib --with-cc ${LLVM_BUILD_DIR}/bin/clang \
    --with-llvm-config ${LLVM_BUILD_DIR}/bin/llvm-config && \
    make -j4


RUN apt-get update && \
    apt-get install -y \
    libgoogle-perftools-dev \
    libsqlite3-dev \
    python3-psutil \
    python3-pip

RUN pip3 install wllvm --break-system-packages

RUN cd klee && \
    mkdir build && \
    cd build && \
    cmake -DENABLE_SOLVER_STP=ON  \
    -DENABLE_POSIX_RUNTIME=ON  \
    -DENABLE_KLEE_UCLIBC=ON \
    -DKLEE_UCLIBC_PATH=${EXPERIMENT_HOME}/klee-uclibc/ \
    -DLLVM_CONFIG_BINARY=${LLVM_BUILD_DIR}/bin/llvm-config \
    -DLLVMCC=${LLVM_BUILD_DIR}/bin/clang \
    -DLLVMCXX=${LLVM_BUILD_DIR}/bin/clang++ .. && \
    make -j4

RUN apt-get update && apt-get install -y gperf pkg-config libprotobuf-dev protobuf-compiler libprotoc-dev && rm -rf /var/lib/apt/lists/*

ENV KLEE_BUILD_DIR ${EXPERIMENT_HOME}/klee/build
ENV KLEE ${KLEE_BUILD_DIR}/bin/klee
ENV KTEST_TOOL ${KLEE_BUILD_DIR}/bin/ktest-tool
ENV KLEE_INCLUDE ${EXPERIMENT_HOME}/klee/include
ENV KLEE_STATS ${KLEE_BUILD_DIR}/bin/klee-stats


WORKDIR /artifact


CMD ["bash"]
