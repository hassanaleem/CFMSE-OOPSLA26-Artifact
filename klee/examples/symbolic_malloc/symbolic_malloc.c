#include "klee/klee.h"
#include <stdlib.h>

int main() {
  int *arr = (int *)malloc(sizeof(int) * 5);
  int count = 0;
  klee_make_symbolic((void *)arr, sizeof(int) * 5, "arr");

  for (int i = 0; i < 5; i++) {
    if (arr[i] > 0)
      count++;
  }

  return count > 0;
}