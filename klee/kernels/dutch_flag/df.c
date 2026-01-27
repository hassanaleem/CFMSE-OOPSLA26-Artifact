#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>

void swap(unsigned int* a, unsigned int* b){
    unsigned int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void flag(unsigned int *arr, unsigned int N){
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = N-1;

    while (j <= k) {
        #ifdef MERGE
        klee_open_merge();
        #endif
        if (arr[j] == 0){
            swap(arr+i, arr+j);           
            i++;
            j++;
        } else if (arr[j] == 2) {
            swap(arr+j, arr+k);
            k--;
        } else {
            j++;
        }
        #ifdef MERGE
        klee_close_merge();
        #endif
    }

}

int main() {
    unsigned int N = SIZE;
    unsigned int *arr = (unsigned int*)malloc(N*sizeof(unsigned int));
    klee_make_symbolic(arr, N*sizeof(unsigned int), "arr");
    
    klee_assume(arr[0] == 0);
    klee_assume(arr[1] == 1);
    klee_assume(arr[2] == 2);
    for(unsigned int i = 0; i < N; i++) {
        klee_assume((arr[i] == 0) | (arr[i] == 1) || arr[i] == 2);
    }
    
    flag(arr, N);

    // verify the result
    for(unsigned int i = 0; i < N-1; i++) {
        klee_assert(arr[i]  <= arr[i+1]);
    }
    
    return 0;
}