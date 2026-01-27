#include "klee/klee.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum(int num_args, ...) {
  int val = 0;
  va_list ap;
  int i;

  va_start(ap, num_args);
  for (i = 0; i < num_args; i++) {
    val += va_arg(ap, int);
  }
  va_end(ap);

  return val;
}

int mul(int num_args, ...) {
  int val = 0;
  va_list ap;
  int i;

  va_start(ap, num_args);
  for (i = 0; i < num_args; i++) {
    val *= va_arg(ap, int);
  }
  va_end(ap);

  return val;
}

struct Node {
  int a, b;
};

int main(int argc, char **argv) {
  struct Node temp = {10,10};
  // print the struct temp
  printf("temp.a = %d, temp.b = %d\n", temp.a, temp.b);

  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  printf("Sum of 15 and 56 = %d\n", sum(2, a, b));
  printf("Sum of 15 and 56 = %d\n", mul(2, a, b));
  return 0;
}
