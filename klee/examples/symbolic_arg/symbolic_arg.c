#include "klee/klee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  int a = 10;

  for (int i = 0; i < 5; i++) {
    if (strcmp(argv[0], "add") == 0) {
      a += 10;
    } else {
      a -= 10;
    }
  }

  printf("a = %d\n", a);
}
