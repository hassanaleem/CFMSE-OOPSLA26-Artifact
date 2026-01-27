/*
 *  C Program to Implement Bitonic sort
 */
#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>
// #define SIZE 8
#define SWAP(x,y) t = x; x = y; y = t;
 
void compare();
void bitonicmerge(int, int, int);
void recbitonic(int, int, int);
void sort();
 
int data[SIZE];
int up = 1;
int down = 0;
 
int main()
{
    // int i;
 
    // printf("\nEnter the data");
    // for (i = 0;i < SIZE ;i++)
    // {
    //     scanf("%d", &data[i]);
    // }

    klee_make_symbolic(data, sizeof(data), "data");

    sort();
#ifdef VERIFY
    for (int i = 0;i < SIZE-1;i++)
    {
        klee_assert(data[i] <= data[i+1]);
    }
    printf("verified\n");
#endif
    return 0;
}
/*
 * compare and swap based on dir
 */
void compare(int i, int j, int dir)
{
    int t;
#ifdef MERGE
    klee_open_merge();
#endif
    if (dir == (data[i] > data[j]))
    {
        SWAP(data[i], data[j]);
    }
#ifdef MERGE
    klee_close_merge();
#endif
}
/*
 * Sorts a bitonic sequence in ascending order if dir=1
 * otherwise in descending order
 */
void bitonicmerge(int low, int c, int dir)
{
    int k, i;
#ifdef MERGE
    klee_open_merge();
#endif
    if (c > 1)
    {
         k = c / 2;
        for (i = low;i < low+k ;i++)
            compare(i, i+k, dir);    
        bitonicmerge(low, k, dir);
        bitonicmerge(low+k, k, dir);    
    }
#ifdef MERGE
    klee_close_merge();
#endif
}
/*
 * Generates bitonic sequence by sorting recursively
 * two halves of the array in opposite sorting orders
 * bitonicmerge will merge the resultant data
 */
void recbitonic(int low, int c, int dir)
{
    int k;
#ifdef MERGE
    klee_open_merge();
#endif
    if (c > 1)
    {
        k = c / 2;
        recbitonic(low, k, up);
        recbitonic(low + k, k, down);
        bitonicmerge(low, c, dir);
    }
#ifdef MERGE
    klee_close_merge();
#endif
}
 
/*
 * Sorts the entire array
 */
void sort()
{
    recbitonic(0, SIZE, up);
}