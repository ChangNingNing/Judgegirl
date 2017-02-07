#include "matrix.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT unsigned long
#define MAXN 2048
UINT Bt[MAXN][MAXN];

#define MAX_THREAD 16
typedef struct {
    UINT *aPtr, *cPtr;
    int l, r;
} Arg;

int n;

int Min(int x, int y) { return x<y? x: y;}

void *myMul(void *argument){
    Arg *arg = (Arg *)argument;
    UINT *A = arg->aPtr, *C = arg->cPtr;
    int l = arg->l, r = arg->r;
    free(arg);

    UINT *aBase = A+l*MAXN, *cBase = C+l*MAXN;
    for(int i=l; i<r; i++, aBase+=MAXN, cBase+=MAXN){
        UINT *cPtr = cBase;
        UINT *bBase = (UINT *)Bt;
        for(int j=0; j<n; j++, cPtr++, bBase+=MAXN){
            UINT sum = 0;
            UINT *aPtr = aBase, *bPtr = bBase;
            int k;
            for(k=0; k+8<n; k += 8){
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
            }
            for(; k<n; k++)
                sum += *aPtr * *bPtr, aPtr++, bPtr++;
            *cPtr = sum;
        }
    }
    pthread_exit(NULL);
}

void multiply(int N, UINT A[][2048], UINT B[][2048], UINT C[][2048]) {
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            Bt[i][j] = B[j][i];

    n = N;
    pthread_t threads[MAX_THREAD];
    int Block = (n + MAX_THREAD - 1)/MAX_THREAD;
    for(int i=0, tID=0; i<n; i+=Block, tID++){
        Arg *arg = (Arg *)malloc(sizeof(Arg));
        arg->aPtr = (UINT *)A, arg->cPtr = (UINT *)C;
        arg->l = i;
        arg->r = Min(i+Block, n);
        pthread_create(&threads[tID], NULL, myMul, (void *)arg);
    }
    for(int i=0, tID=0; i<n; i+=Block, tID++)
        pthread_join(threads[tID], NULL);
    return;
}
