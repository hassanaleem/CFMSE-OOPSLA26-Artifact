export LLVM_COMPILER_PATH=${LLVM_BUILD_DIR}/bin/
export LLVM_COMPILER=clang
CFLAGS="-g -O1 -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__"
# CPPFLAGS="-I.. -I../lib -I../../lib -DGNULIB_PORTCHECK=0"
rm -rf obj-llvm
mkdir -p obj-llvm
cd obj-llvm

# CC=wllvm ../configure --disable-nls CFLAGS="-g -O1 -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__"
CC=wllvm ../configure --disable-nls CFLAGS="${CFLAGS}" CPPFLAGS="${CPPFLAGS}"
make -C lib
# make -C src chcon
make -C src chcon mkdir mkfifo touch unexpand split chown chmod arch hostname

find . -executable -type f | xargs -I '{}' extract-bc '{}'

cd ..
