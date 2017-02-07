#include "matrix.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT unsigned long
#define MAXN 2048

UINT Bt[MAXN][MAXN];

void multiply(int N, UINT A[][2048], UINT B[][2048], UINT C[][2048]) {
	#pragma omp parallel for
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			Bt[i][j] = B[j][i];

	#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            unsigned long sum = 0;    // overflow, let it go.
            for (int k = 0; k < N; k++)
                sum += A[i][k] * Bt[j][k];
            C[i][j] = sum;
        }
    }
}
