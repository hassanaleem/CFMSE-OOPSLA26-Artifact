#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <klee/klee.h>

int connected_comp(bool *graph, int * cc, int n) {
    for (int s = 0; s < n; s++) cc[s] = s;
    bool changed = true;
    // count different connected components
    while (changed) {
        changed = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                #ifdef MERGE
                klee_open_merge();
                #endif
                if (graph[i*n+j]) {
                    if (cc[i] > cc[j]){
                        cc[i] = cc[j];
                        changed = true;
                    }
                }
                #ifdef MERGE
                klee_close_merge();
                #endif
            }
        }
    }
    // initialize histogram
    int *hh = (int*)malloc(n * sizeof(int));
    for (int s = 0; s < n; s++) hh[s] = 0;
    // update histogram
    for (int s = 0; s < n; s++) hh[cc[s]]++;
    // count non-zero histogram entries
    int numcc = 0;
    for (int s = 0; s < n; s++) if (hh[s] > 0) numcc++;
    return numcc;
}

bool cc_verify(bool *graph, int *cc, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i*n+j]) {
                if (cc[i] != cc[j]) return false;
            }
        }
    }
    return true;
}

int main() {
    int n = SIZE;
    bool *graph = (bool*)malloc(n*n*sizeof(bool));
    klee_make_symbolic(graph, n*n*sizeof(bool), "graph");
    int *cc = (int*)malloc(n*sizeof(int));
    klee_make_symbolic(cc, n*sizeof(int), "cc");
    int numcc = connected_comp(graph, cc, n);
    //printf("number of connected components: %d\n", numcc);
    #ifdef VERIFY
    klee_assert(cc_verify(graph, cc, n));
    printf("verified\n");
    #endif 
    return 0;
}
