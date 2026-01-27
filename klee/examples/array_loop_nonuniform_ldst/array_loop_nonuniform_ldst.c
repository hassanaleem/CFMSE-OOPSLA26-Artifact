#include <stdio.h>
#include <klee/klee.h>

void foo(int *arr1, int* arr2) {

  int temp;

  for(int i = 0; i < 10; i++) {
    if(arr2[i] <= arr1[2]) {
      temp = arr1[i];
      temp++;
      temp*=10;  
      temp-=15;
      arr1[i] = temp;
    } else {
      temp = arr2[i];
      temp+=50;
      temp*=20;
      temp-=-5;
      arr2[i] = temp;
    }
  }

  if (arr1[0] == 0) {
    printf("arr1[0] is 0 in this path!\n");
  }

}

#define N 10

int main() {
  int arr1[N];
  int arr2[N];

  klee_make_symbolic(&arr1, sizeof(arr1), "arr1");
  klee_make_symbolic(&arr2, sizeof(arr2), "arr1");

  foo(arr1, arr2);
}
