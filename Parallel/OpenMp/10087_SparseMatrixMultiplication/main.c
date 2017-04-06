#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

#define MAXN 1000001
uint32_t A[MAXN][3], B[MAXN][3];
int N, M, R, nA, nB;
uint32_t *ptrA[MAXN];
int nPtr;

int BSinB(int value){
	int l = 0, r = nB-1;
	while(l <= r){
		int mid = (l+r)/2;
		if(value <= B[mid][0]) r = mid-1;
		else l = mid+1;
	}
	return l;
}

int main() {
    scanf("%d %d %d", &N, &M, &R);
    scanf("%d %d", &nA, &nB);
    for (int i = 0; i < nA; i++)
        scanf("%d %d %d", &A[i][0], &A[i][1], &A[i][2]);
    for (int i = 0; i < nB; i++)
        scanf("%d %d %d", &B[i][0], &B[i][1], &B[i][2]);

	ptrA[0] = A[0], nPtr = 1;
	for (int i = 1; i < nA; i++){
		if (A[i][0] != A[i-1][0])
			ptrA[nPtr++] = A[i];
	}

	uint32_t hash = 0;	
	#pragma omp parallel for reduction (+:hash)
	for (int i = 0; i < nPtr; i++){
		int *tmpC = (int *)calloc(R, sizeof(int));
		for (uint32_t *j = ptrA[i]; j[0]==ptrA[i][0]; j+=3){
			for (int k = BSinB(j[1]); B[k][0]==j[1]; k++){
				tmpC[B[k][1]] += j[2]*B[k][2];
			}
		}

		for (int j=0; j < R; j++)
			if (tmpC[j])
				hash += encrypt((ptrA[i][0]+1)*(j+1), tmpC[j]);
		free(tmpC);
	}

    printf("%u\n", hash);
    return 0;
}
