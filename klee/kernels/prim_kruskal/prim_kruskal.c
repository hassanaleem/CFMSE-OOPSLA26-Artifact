#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>

int minKey(int* key, bool* mstSet, int n)
{
    int min = INT_MAX;
    int min_index;
 
    for (int v = 0; v < n; v++) {
        #ifdef MERGE
        klee_open_merge();
        #endif
        if (mstSet[v] == false && key[v] < min) {
            min = key[v]; 
            min_index = v;
        }
        #ifdef MERGE
        klee_close_merge();
        #endif
    }
 
    return min_index;
}

int primMST(int *graph, int *parent, int *key, bool* mstSet, int n)
{
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX; 
        mstSet[i] = false;
    }
 
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;
 
        for (int v = 0; v < n; v++) {
            #ifdef MERGE
            klee_open_merge();
            #endif
            if (graph[u * n + v] && mstSet[v] == false
                && graph[u * n + v] < key[v]) {
                parent[v] = u; 
                key[v] = graph[u * n + v];
            }
            #ifdef MERGE
            klee_close_merge();
            #endif
        }
    }
    // computing cost of the MST
    int minCost = 0;
    for (int i = 0; i < n; i++) {
        minCost += key[i];
    }
    return minCost;
}

typedef struct _edge {
  int u, v, wt;
} edge;

int comparator(const void *p, const void *q) // used by qsort()
{
  int l = ((edge *)p)->wt;
  int r = ((edge *)q)->wt;
  return (l - r);
}

void makeSet(int *parent, int *rank, int n) {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    rank[i] = 0;
  }
}

int findParent(int *parent, int component) {
#ifdef MERGE
  klee_open_merge();
#endif
  if (parent[component] == component) {
#ifdef MERGE
    klee_close_merge();
#endif
    return component;
  }

  return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int *parent, int *rank, int n) {
  // this function unions two set on the basis of rank
  // as shown below
  u = findParent(parent, u);
  v = findParent(parent, v);
#ifdef MERGE
  klee_open_merge();
#endif

  if (rank[u] < rank[v]) {
    parent[u] = v;
  } else if (rank[u] > rank[v]) {
    parent[v] = u;
  } else {
    parent[v] = u;
    rank[u]++; // since the rank increases if the ranks of two sets are same
  }
#ifdef MERGE
  klee_close_merge();
#endif
}

int kruskalMST(edge *edges, int *parent, int *rank, int n) {
  // if cfm works with ulibc then we can keep the qsort and remove assumption
  qsort(edges, n, sizeof(edge), comparator);

  makeSet(parent, rank, n); // function to initialize parent[] and rank[]

  int minCost = 0; // to store the minimun cost

  for (int i = 0; i < n; i++) {
    int v1 = findParent(parent, edges[i].u);
    int v2 = findParent(parent, edges[i].v);
    int wt = edges[i].wt;

#ifdef MERGE
    klee_open_merge();
#endif
    if (v1 != v2) // if the parents are different that means they are in
                  // different sets so union them
    {
      unionSet(v1, v2, parent, rank, n);
      minCost += wt;
    }
#ifdef MERGE
    klee_close_merge();
#endif
  }

  return minCost;
}

int main()
{
    // defining graph for kruskal
    int m = SIZE; // #edges
    int n = SIZE; // #nodes
    
    edge *edges = (edge *)malloc(m * sizeof(edge));
    int *parentk = (int *)malloc(m * sizeof(int));
    int *rank = (int *)malloc(m * sizeof(int));

    klee_make_symbolic(edges, m * sizeof(edge), "edges");
    klee_make_symbolic(parentk, n * sizeof(int), "parentk");
    klee_make_symbolic(rank, n * sizeof(int), "rank");
    
    for (int l = 0; l < m; l++){
      klee_assume(edges[l].u >= 0);
      klee_assume(edges[l].u < n);
      klee_assume(edges[l].v >= 0);
      klee_assume(edges[l].v < n);
      klee_assume(edges[l].u != edges[l].v);
      klee_assume(edges[l].wt >= 0);
      for (int k = 0; k < l; k++){
        klee_assume(edges[l].u != edges[k].u); 
        klee_assume(edges[l].v != edges[k].v);
        klee_assume(edges[l].u != edges[k].v);
        klee_assume(edges[l].v != edges[k].u);
      }
    }
    
    // defining graph for prim
    int *graph = (int*)malloc(n * n * sizeof(int));
    int *parentp = (int*)malloc(n * sizeof(int));
    int *key = (int*)malloc(n * sizeof(int));
    bool *mstSet = (bool*)malloc(n * sizeof(bool));
    
    klee_make_symbolic(graph, n * n * sizeof(int), "graph");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
          for (int l = 0; l < m; l++){
            if ((edges[l].u == i && edges[l].v == j) 
                || (edges[l].v == i && edges[l].u == j))
            {
              klee_assume(graph[i*n+j] == edges[l].wt);
              klee_assume(graph[j*n+i] == edges[l].wt);
            } else {
              klee_assume(graph[i*n+j] == 0);
              klee_assume(graph[j*n+i] == 0);
            }
          }
        }
    }

    int pminCost = primMST(graph, parentp, key, mstSet, n);
    int kminCost = kruskalMST(edges, parentk, rank, m);

    klee_assert(pminCost == kminCost);

    return 0;
}