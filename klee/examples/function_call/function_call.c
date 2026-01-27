#include "klee/klee.h"
int foo(int x, int y){
  int t = 5;
  if (x + 100 >= 0) {
    t += 10;
  }
  else {
    t -= 468;
  }

  if (y < t) {
    t *= y;
  }
  return t;
}

int main(){
  int x = 1, y = 1;
  klee_make_symbolic((void*)&x, sizeof(int), "x");
  klee_make_symbolic((void*)&y, sizeof(int), "y");
  if (foo(x, 10)) return -1;
  if (foo(10, y)) return 1;
  return 0;
}