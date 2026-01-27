#include <stdio.h>
#include <klee/klee.h>

void foo(int *arr) {

  int temp;
  int temp2 = arr[0];

  for(int i = 0; i < 10; i++) {
    if(arr[i] >= 5) {
      temp = arr[i];
      temp-=3;
      temp*=10;
      temp-=15;
    } else {
      temp = temp2;
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
  int arr[10];

  // for(int i = 0; i < 20; i++) {
  //   scanf("%d", &arr[i]);
  // }

  klee_make_symbolic(&arr, sizeof(arr), "arr");

  foo(arr);
}
