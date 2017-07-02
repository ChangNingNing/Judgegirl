#include <stdio.h>
#include <stdint.h>

#define MAXN 1024

__device__ __host__ int CeilDiv(int a, int b) { return (a-1)/b + 1; }

void rand_gen(uint32_t cA, uint32_t cB, int N, uint32_t *A, uint32_t *B) {
    uint32_t xA = 2, n = N*N;
	uint32_t xB = 2;

	uint32_t *_A = A;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *_A = xA = (xA * xA + cA + i + j)%n, _A++;
			B[j*N + i] = xB = (xB * xB + cB + i + j)%n;
        }
    }
}

uint32_t signature(int N, uint32_t *A) {
    uint32_t h = 0;
	uint32_t *_A = A;
    for (int i = N*N; i > 0; i--)
		h = (h + *_A) * 2654435761LU, _A++;
    return h;
}

__global__ void myMatrixMul(int N, uint32_t *cuC, uint32_t *cuA, uint32_t *cuTransB){
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	if (tid >= N*N) return;
	int x = tid / N;
	int y = tid % N;

	uint32_t *_A = cuA + x*N;
	uint32_t *_B = cuTransB + y*N;
	uint32_t sum = 0;
	for (int k=N; k>0; k--)
		sum += *_A * *_B, _A++, _B++;
	cuC[x*N + y] = sum;
}

uint32_t A[MAXN*MAXN], B[MAXN*MAXN], C[MAXN*MAXN];

int main() {
    int N;
    uint32_t S1, S2;
    scanf("%d %u %u", &N, &S1, &S2);
    rand_gen(S1, S2, N, A, B);

	uint32_t *cuA, *cuB, *cuC;
	cudaMalloc( &cuA, sizeof(uint32_t)*N*N );
	cudaMalloc( &cuB, sizeof(uint32_t)*N*N );
	cudaMalloc( &cuC, sizeof(uint32_t)*N*N );

	cudaMemcpy( cuA, A, sizeof(uint32_t)*N*N, cudaMemcpyHostToDevice);
	cudaMemcpy( cuB, B, sizeof(uint32_t)*N*N, cudaMemcpyHostToDevice);

	dim3 grid(CeilDiv(N*N, 32)), block(32);
	myMatrixMul<<< grid, block >>>( N, cuC, cuA, cuB );
	
	cudaMemcpy( C, cuC, sizeof(uint32_t)*N*N, cudaMemcpyDeviceToHost);
    printf("%u\n", signature(N, C));

	cudaFree(cuA);
	cudaFree(cuB);
	cudaFree(cuC);
    return 0;
}
