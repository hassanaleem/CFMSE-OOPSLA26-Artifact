#include "utf8.h"
#include <assert.h>

int main() {
    char arr[SIZE];
    klee_make_symbolic(arr, SIZE, "arr");
    klee_assume(arr[SIZE-1] == '\0');

    char arr1[SIZE];
    klee_make_symbolic(arr1, SIZE, "arr1");
    klee_assume(arr1[SIZE-1] =='\0');

    void *arr_check = utf8valid(arr);
    void *arr1_check = utf8valid(arr1);
    if (arr_check != 0 && arr1_check != 0)
    {
            if (utf8ncasecmp(arr_check, arr1_check, SIZE-1) == 1)
                    return 1;
            return 0;
    }
    return 1;

}
