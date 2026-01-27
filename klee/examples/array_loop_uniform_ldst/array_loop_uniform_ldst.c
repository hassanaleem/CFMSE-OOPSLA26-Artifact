#include <stdio.h>
#include <klee/klee.h>

void foo(int *arr) {

  int temp;

  for(int i = 0; i < 10; i++) {
    if(arr[i] <= 2) {
      temp = arr[i];
      temp++;
      temp*=10;  
      temp-=15;
      arr[i] = temp;
    } else {
      temp = arr[i];
      temp+=50;
      temp*=20;
      temp-=-5;
      arr[i] = temp;
    }
    
  }
  
  if (arr[0] == -5) {
    printf("arr[0] is 0 in this path!\n");
  }

}

int main() {
  int arr[10];

  klee_make_symbolic(&arr, sizeof(arr), "arr");

  foo(arr);
}
