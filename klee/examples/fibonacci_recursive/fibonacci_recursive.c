#include <stdio.h>
#include <klee/klee.h>

int foo(int n) {

  if ( n == 0 )
      return 0;
   else if ( n == 1 )
      return 1;
   else
      return ( foo(n-1) + foo(n-2) );
}

int main() {
  int n;
  //int n = klee_range(-5, 10, "n");

  klee_make_symbolic(&n, sizeof(n), "n");
  klee_assume(n < 5);

  int output = foo(n);
}
