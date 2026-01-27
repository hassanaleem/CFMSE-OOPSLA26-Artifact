#include <stdio.h>
#include "klee/klee.h"

void foo(int n1, int n2)
{
    while(n1!=n2)
    {
        #ifdef MERGE 
        klee_open_merge();
        #endif
        if(n1 > n2)
            n1 -= n2;
        else
            n2 += -n1;
        #ifdef MERGE
        klee_close_merge();
        #endif
    }
}

int main() {
  int n1, n2;
  klee_make_symbolic(&n1, sizeof(n1), "n1");
  klee_make_symbolic(&n2, sizeof(n2), "n2");

  klee_assume(n1 > 0 && n1 <= 10);
  klee_assume(n2 > 0 && n2 <= 10);

  foo(n1, n2);

  return 0;
}
