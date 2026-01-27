/*
 * First KLEE tutorial: testing a small function
 */

#include "klee/klee.h"
#include <stdio.h>
#define N 7

typedef struct {
  int x;
  int y;
} IntTuple;

IntTuple orig(int *input, int nelems) {
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
  if (sum == -1 * N) {
    printf("this is path A!\n");
  }
  if (mul == 1) {
    printf("this is path B!\n");
  }
  IntTuple result;
  result.x = sum;
  result.y = mul;
  return result;
}

IntTuple transformed(int *input, int nelems) {
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
  if (sum == -1 * N) {
    printf("this is path A!\n");
  }
  if (sum == N) {
    printf("this is path B!\n");
  }
  IntTuple result;
  result.x = sum;
  result.y = mul;
  return result;
}

int main() {
  int a[N];
  klee_make_symbolic(&a, sizeof(a), "a");
  // orig(a, N);
  if (orig(a, N).x != transformed(a, N).x) {
    printf("trasnformation is incorrect!");
  }
  if (orig(a, N).y != transformed(a, N).y) {
    printf("trasnformation is incorrect!");
  }
  return 0;
}
