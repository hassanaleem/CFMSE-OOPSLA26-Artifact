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

int main()
{
    int n = SIZE;
    int *graph = (int*)malloc(n*n*sizeof(int));
    int *parent = (int*)malloc(n*sizeof(int));
    int *key = (int*)malloc(n*sizeof(int));
    bool *mstSet = (bool*)malloc(n*sizeof(bool));
    klee_make_symbolic(graph, n*n*sizeof(int), "graph");
    
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            klee_assume(graph[i * n + j] >= 0);
        }
    }

    int minCost = primMST(graph, parent, key, mstSet, n);

    return 0;
}