export LLVM_COMPILER_PATH=${LLVM_BUILD_DIR}/bin/
export LLVM_COMPILER=clang
CFLAGS="-g -O1 -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__"

./autogen.sh

mkdir -p obj-llvm
cd obj-llvm

CC=wllvm ../configure  CFLAGS="${CFLAGS}" --prefix=/artifact/fig7-coverage/protobuf-c/install
make
make install

cd ..
./install/bin/protoc-c --c_out=. amessage.proto
extract-bc /artifact/fig7-coverage/protobuf-c/install/lib/libprotobuf-c.a -o /artifact/fig7-coverage/protobuf-c/protobuf-c.bc
$CLANG $CFLAGS -emit-llvm -I /artifact/fig7-coverage/protobuf-c/install/include -c amessage.pb-c.c -o amessage.pb-c.bc

