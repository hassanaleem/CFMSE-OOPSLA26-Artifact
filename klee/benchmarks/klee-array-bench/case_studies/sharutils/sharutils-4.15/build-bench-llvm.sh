export LLVM_COMPILER=clang
CFLAGS="-g"

mkdir -p obj-llvm
cd obj-llvm

# CC=wllvm ../configure --disable-nls CFLAGS="-g -O1 -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__"
CC=wllvm ../configure --disable-nls CFLAGS="${CFLAGS}"
make

cd src
find . -executable -type f | xargs -I '{}' extract-bc '{}'

cd ..
cd ..