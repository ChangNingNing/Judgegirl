#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <omp.h>

#define MAXN 100
#define LL long long int
LL DP[MAXN*MAXN];
int pi[MAXN*MAXN];
int Z[MAXN+1], S[MAXN];
int N;

// generate matrix, row-major
uint32_t* rand_gen(uint32_t seed, int R, int C) {
    uint32_t *m = (uint32_t *) malloc(sizeof(uint32_t) * R*C);
    uint32_t x = 2, n = R*C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            x = (x * x + seed + i + j)%n;
            m[i*C + j] = x;
        }
    }
    return m;
}
uint32_t hash(uint32_t x) {
    return (x * 2654435761LU);
}
// output
uint32_t signature(uint32_t *A, int r, int c) {
    uint32_t h = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            h = hash(h + A[i*c + j]);
    }
    return h;
}

uint32_t* D_C(int l, int r){
	if(l==r) return rand_gen(S[l], Z[l], Z[l+1]);

	int k = pi[l*N+r];
	int z1 = Z[l], z2 = Z[k+1], z3 = Z[r+1];
	uint32_t *A = D_C(l, k), *B = D_C(k+1, r);
	uint32_t *Bt = (uint32_t *)malloc(sizeof(uint32_t) * z3 * z2);
	uint32_t *C = (uint32_t *)malloc(sizeof(uint32_t) * z1 * z3);

#pragma omp parallel
{
	#pragma omp for
	for(int i=0; i<z3; i++){
		uint32_t *pBt = Bt+i*z2, *pB = B+i;
		for(int j=0; j<z2; j++, pB+=z3)
			pBt[j] = *pB;
	}

	#pragma omp for
	for(int i=0; i<z1; i++){
		uint32_t *pC = C + i*z3;
		for(int j=0; j<z3; j++){
			uint32_t sum = 0;
			uint32_t *pA = A+i*z2, *pBt = Bt+j*z2;
			for(int k=0; k<z2; k++)
				sum += pA[k] * pBt[k];
			pC[j] = sum;
		}
	}
}
	free(A), free(B), free(Bt);
	return C;
}

int main(){
	while(scanf("%d", &N)==1){
		for(int i=0; i<=N; i++)
			scanf("%d", &Z[i]);
		for(int i=0; i<N; i++)
			scanf("%d", &S[i]), DP[i*N+i] = 0, pi[i*N+i] = i;

		// DP
		#pragma omp parallel
		for(int l=1; l<N; l++){
			#pragma omp for
			for(int i=0; i < N-l; i++){
				int j = i + l;
				int minK;
				LL min = 0x7fffffffffffffff;
				LL *ptr1 = DP+i*N, *ptr2 = DP+j*N;
				int Ztmp = Z[i]*Z[j+1];
				for(int k=i; k<j; k++){
					LL tmp = ptr1[k] + ptr2[k+1] + Z[k+1] * Ztmp;
					if(tmp < min)
						min = tmp, minK = k; 
				}
				ptr1[j] = ptr2[i] = min;
				pi[i*N+j] = minK;
			}
		}

		// Matrix Multiplication
		uint32_t *C = D_C(0, N-1);
		printf("%u\n", signature(C, Z[0], Z[N]));
	}
	return 0;
}
