#include <stdio.h>
#include <klee/klee.h>

#define SIZE 10

void foo(int *in1, int *in2, int *out) {
  for(int i = 0; i < SIZE; i++) {
    if (in1[i] >= in2[i])
      out[i] = in1[i] - in2[i];
    else
      out[i] = in2[i] - in1[i];
  }
}

int main() {
  int in1[SIZE];
  int in2[SIZE];
  int out[SIZE];
  
  // for (int i = 0; i < SIZE; i++) {
  //   klee_assume(in1[i] >= 0);
  //   klee_assume(in2[i] >= 0);
  // }

  klee_make_symbolic(&in1, sizeof(in1), "arr");
  klee_make_symbolic(&in2, sizeof(in2), "arr");

  foo(in1, in2, out);

  for (int i = 0; i < SIZE; i++)
    klee_assert(out[i] >= 0);
}
