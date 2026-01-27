#include <stdio.h>
#include <klee/klee.h>

void foo(int *arr1, int* arr2) {

  int temp;

  for(int i = 0; i < 10; i++) {
    if(arr1[i] >= 5) {
      temp = arr1[i];
      temp++;
      temp*=10;
      temp-=15;
    } else {
      temp = arr1[i];
      temp+=5;
      temp*=3;
      temp-=2;
    }
  }

    for(int i = 0; i < 10; i++) {
    if(arr2[i] >= 5) {
      temp = arr2[i];
      temp++;
      temp*=10;
      temp-=15;
    } else {
      temp = arr2[i];
      temp+=5;
      temp*=3;
      temp-=2;
    }
  }
  
  // for(int i = 0; i < 10; i++) {
  //   printf("arr[%d]=%d\n", i, arr[i]);
  // }
}

int main() {
  int arr1[10];
  int arr2[10];

  // for(int i = 0; i < 20; i++) {
  //   scanf("%d", &arr[i]);
  // }

  klee_make_symbolic(&arr1, sizeof(arr1), "arr");

  foo(arr1, arr2);
}
