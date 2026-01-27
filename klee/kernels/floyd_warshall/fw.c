
#include <klee/klee.h>
#include <stdio.h>
#include <stdlib.h>

void floyd_warshall(int *dist, int n) {
  for (int v = 0; v < n; v++)
    dist[v * n + v] = 0;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int d = dist[i * n + k] + dist[k * n + j];
#ifdef MERGE
        klee_open_merge();
#endif
        if (d < dist[i * n + j]) {
          dist[i * n + j] = d;
        }
#ifdef MERGE
        klee_close_merge();
#endif
      }
    }
  }
}

void floyd_warshall_branchless(int *dist, int n) {
  for (int v = 0; v < n; v++)
    dist[v * n + v] = 0;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int d = dist[i * n + k] + dist[k * n + j];

        // if (d < dist[i * n + j]) {
        //   dist[i * n + j] = d;
        // }
        dist[i * n + j] = d * (d < dist[i * n + j]) +
                          dist[i * n + j] * (d >= dist[i * n + j]);
      }
    }
  }
}

int main() {
  int n = SIZE;
  int *dist = (int *)malloc(n * n * sizeof(int));
  int *dist_copy = (int *)malloc(n * n * sizeof(int));
  klee_make_symbolic(dist, n * n * sizeof(int), "dist");

  for (int i = 0; i < n * n; i++) {
    dist_copy[i] = dist[i];
  }

  floyd_warshall(dist, n);

#ifdef VERIFY
  printf("verifying the result!\n");
  floyd_warshall_branchless(dist_copy, n);
  
  // verify the result
  for (int i = 0; i < n * n; i++) {
    // printf("%d\n", i);
    klee_assert(dist[i] == dist_copy[i]);
  }
  printf("verified!\n");
#endif

  return 0;
}