#include "utf8.h"
#include <klee/klee.h>
#include <stdio.h>


int
main(int argc, char **argv)
{
        int size = 20;
        
        char arr[size];
        klee_make_symbolic(arr, size, "arr");
        klee_assume(arr[size - 1] == '\0');

        char arr1[size];
        klee_make_symbolic(arr1, size, "arr1");
        klee_assume(arr1[size - 1] =='\0');

        void *arr_check = utf8valid(arr);
        void *arr1_check = utf8valid(arr1);
        if (arr_check == 0 && arr1_check == 0)
        {
                if (utf8ncasecmp(arr, arr1, size) == 0)
                        return 1;
                return 0;
        }
        return 1;
}
