#include "matrix_multiplication.h"
#include <stdio.h>
#include <string.h>

void matrix_multiplication(int N, int **ptrA, int M, int **ptrB, int S, int *result){
	memset(result, 0, sizeof(int)*S*S);
	for(int i=0; i<N; i++){
		int x = ptrA[1][i];
		int k = ptrA[2][i];
		for(int j=0; j<M; j++){
			if(k != ptrB[1][j]) continue;
			int y = ptrB[2][j];
			result[x*S + y] += ptrA[0][i] * ptrB[0][j];
		}
	}
	return;
}
