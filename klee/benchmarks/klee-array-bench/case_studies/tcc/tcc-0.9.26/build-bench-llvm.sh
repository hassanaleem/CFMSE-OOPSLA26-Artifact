mkdir -p obj-llvm
cd obj-llvm

# CC=wllvm ../configure --disable-nls CFLAGS="-g -O1 -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__"
LLVM_COMPILER_PATH=${LLVM_BUILD_DIR}/bin/ LLVM_COMPILER=clang ../configure  --extra-cflags="-g -O1 -Xclang -disable-llvm-passes" --cc=wllvm
make

find . -executable -type f | xargs -I '{}' extract-bc '{}'

cd ..