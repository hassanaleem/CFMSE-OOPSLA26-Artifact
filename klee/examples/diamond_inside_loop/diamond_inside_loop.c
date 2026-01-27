/*
 * First KLEE tutorial: testing a small function
 */

#include "klee/klee.h"
#include <stdio.h>
#define N 7

void foo(int *input, int nelems) {
  int sum = 0;
  int mul = 128;
  for (int i = 0; i < nelems; i++) {
    if (input[i] == 10) {
      mul *= 2;
      sum += 1;
    } else if (input[i] == -10) {
      sum += -1;
      mul /= 2;
    }
  }
  // if (sum == N) {
  //   printf("calling function A!\n");
  // }
  if (mul == 1) {
    printf("calling function B!\n");
  }
}

void optimized_foo(int *input, int nelems) {
  int sum = 0;
  int mul = 128;
  for (int i = 0; i < nelems; i++) {
    // branches remove by manually inserting
    // select operations
    int t1 = input[i] == 10 ? 2 : 1;
    mul *= t1;
  
    int t2 = input[i] == 10 ? 1 : 0;
    int t3 = input[i] == -10 ? -1 : t2; 
    sum += t3;

    int t4 = input[i] == -10 ? 2 : 1;
    mul /= t4;
  }
  if (sum == N) {
    printf("calling function A!\n");
  }
  // if (mul == 1) {
  //   printf("calling function B!\n");
  // }
}

int main() {
  int a[N];
  klee_make_symbolic(&a, sizeof(a), "a");
  foo(a, N);
  // optimized_foo(a, N);
  return 0;
}
