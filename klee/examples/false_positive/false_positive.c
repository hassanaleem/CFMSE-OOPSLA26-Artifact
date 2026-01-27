#include <stdio.h>
#include <klee/klee.h>

int main() {
  int arr[10]; int arr2[10];
  int i;
  int j;
  int y;
  klee_make_symbolic(&y, sizeof(y), "y");

  for(int j = 0; j < 10; j++) {
    if (y < 10){
      i = 8; i++; arr[i] = 10;
    } else {
      i = 9; i++;
      j = 9; j++; arr2[j] = 10;
    }
  }
  //printf("Done! \n");

  return 0;
}
