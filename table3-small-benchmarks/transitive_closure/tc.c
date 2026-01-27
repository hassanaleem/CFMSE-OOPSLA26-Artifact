
#include <klee/klee.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void transitive_closure(bool *graph, int n) {
  for (int v = 0; v < n; v++)
    graph[v * n + v] = true;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        bool d = graph[i * n + k] & graph[k * n + j];
#ifdef MERGE
        klee_open_merge();
#endif
        if (d | graph[i * n + j]) {
          graph[i * n + j] = d;
        }
#ifdef MERGE
        klee_close_merge();
#endif
      }
    }
  }
}

void transitive_closure_branchless(bool *graph, int n) {
  for (int v = 0; v < n; v++)
    graph[v * n + v] = true;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        bool d = graph[i * n + k] & graph[k * n + j];
        bool c = d | graph[i * n + j];
        graph[i * n + j] = c * d + graph[i * n + j] * !c;
      }
    }
  }
}

int main() {
  int n = SIZE;
  bool *graph1 = (bool *)malloc(n * n * sizeof(bool));
  bool *graph2 = (bool *)malloc(n * n * sizeof(bool));

  klee_make_symbolic(graph1, n * n * sizeof(bool), "graph");

  // Copy graph to graph2
  for (int i = 0; i < n * n; i++) {
    graph2[i] = graph1[i];
  }
  transitive_closure(graph1, n);
#ifdef VERIFY
  transitive_closure_branchless(graph2, n);

  // verify the results are the same
  for (int i = 0; i < n * n; i++) {
    klee_assert(graph1[i] == graph2[i]);
  }
  printf("Verified!\n");
#endif

  return 0;
}