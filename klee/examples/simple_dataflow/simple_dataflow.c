#include "klee/klee.h"

int main() {
  int a = 0, b = 0;

  klee_make_symbolic((void *)&a, sizeof(a), "a");

  a = a + 100;
  b = b * 5;

  return a + b;
}
