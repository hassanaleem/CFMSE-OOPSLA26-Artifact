#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "klee/klee.h"

void lup(double *a, int *p, int n) {
    int temp_ind, pivot_ind = 0;
    double pivot, temp_row, temp;

    for (int j = 0; j < n; ++j) {
      pivot = 0;
      for (int i = j; i < n; ++i) {
        if (fabs(a[i*n+j]) > fabs(pivot)) {
          pivot = a[i*n+j]; 
          pivot_ind = i;
        }
      }
      
      for (int m = 0; m < n; ++m) {
        temp_row = a[j*n+m];
        a[j*n+m] = a[pivot_ind*n+m];
        a[pivot_ind*n+m] = temp_row;
      }

      temp_ind  = p[j];
      p[j] = p[pivot_ind];
      p[pivot_ind] = temp_ind;

      for (int k = j+1; k < n; ++k) {
        temp = a[k*n+j] /= a[j*n+j];
        for (int l = j+1; l < n; ++l) {
          a[k*n+l] -= temp*a[j*n+l];
        }
      }
    }
}

int main() {
    int n = 3;
    int *p = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }

    double *a = (double*)malloc(n*n*sizeof(double));
    klee_make_symbolic((double*)a, n*n*sizeof(double), "x");

    lup(a, p, n);

    return 0;
}