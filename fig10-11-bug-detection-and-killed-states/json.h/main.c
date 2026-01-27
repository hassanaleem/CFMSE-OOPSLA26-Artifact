#include "json.h"
#include <klee/klee.h>

int main() {
    // int SIZE = 16;
    char arr[SIZE];
    klee_make_symbolic(arr, SIZE, "arr");
    klee_assume(arr[SIZE-1] == '\0');
    json_parse(arr, SIZE);

    // size_t size = 0;
    // klee_make_symbolic(size, sizeof(size), "size");


    // void *pretty = json_write_pretty(&arr, 0, 0, &size);
    return 0;
}
