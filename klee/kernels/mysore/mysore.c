#include <klee/klee.h>
#include <stdlib.h>

int main() {
    int k;
    // Make k symbolic
    klee_make_symbolic(&k, sizeof(k), "k");

    int a[SIZE];
    // Make the entire array symbolic so we can reason about its elements
    klee_make_symbolic(a, sizeof(a), "a");

    // Check that k is within valid bounds [0, SIZE-1]
    if (k >= 0 && k < SIZE) {
        // Check for specific values at a[0] and a[k]
        if (a[0] == 23 && a[k] == 42) {
            int x;
            // Make x symbolic to explore different loop behaviors
            klee_make_symbolic(&x, sizeof(x), "x");

            // Subtract k from x until x becomes negative.
            while (x >= 0) {
                x = x - k;
            }
        }
    }
    return 0;
}

