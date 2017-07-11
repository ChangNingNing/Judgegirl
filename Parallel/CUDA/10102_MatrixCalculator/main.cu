#include <stdio.h>
#include <stdint.h>
#define MAXN 1024
#define SeqSize 4

__device__ __host__ int CeilDiv(int a, int b) { return (a-1)/b + 1; }

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
    cuC[tid] = sum;
}

__global__ void myMatrixAdd(int N, uint32_t *cuA, uint32_t *cuB){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
	cuA[tid] += cuB[tid];
}

void rand_gen(uint32_t c, int N, uint32_t *A) {
    uint32_t x = 2, n = N*N;
	uint32_t *_A = A;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            _A[j] = x = (x * x + c + i + j)%n;
		_A += N;
    }
}

void rand_gen_t(uint32_t c, int N, uint32_t *A) {
    uint32_t x = 2, n = N*N;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[j*N+i] = x = (x * x + c + i + j)%n;
}

uint32_t signature(int N, uint32_t *A) {
    uint32_t h = 0;
	uint32_t *_A = A;
	for (int i=N*N; i>0; i--, _A++)
		h = (h + *_A) * 2654435761LU;
    return h;
}

uint32_t IN[6][MAXN*MAXN];

int main() {
    int N, S[6];
    scanf("%d", &N);
    for (int i = 0; i < 6; i++)
		scanf("%d", &S[i]);

	#pragma omp parallel for
	for (int i=0; i<6; i++) {
		if (i == 0 || i == 2)
			rand_gen(S[i], N, IN[i]);
		else
			rand_gen_t(S[i], N, IN[i]);
	}

	uint32_t *cuIn[6], *cuTmp[4];
	for (int i=0; i<6; i++){
		cudaMalloc( &cuIn[i], sizeof(uint32_t)*N*N );
		cudaMemcpy( cuIn[i], IN[i], sizeof(uint32_t)*N*N, cudaMemcpyHostToDevice);
	}
	for (int i=0; i<4; i++)
		cudaMalloc( &cuTmp[i], sizeof(uint32_t)*N*N );

	dim3 grid(CeilDiv(N*N, 32)), block(32);
	// AB
	myMatrixMul<<< grid, block >>>(N, cuTmp[0], cuIn[0], cuIn[1]);
	// CD
	myMatrixMul<<< grid, block >>>(N, cuTmp[1], cuIn[2], cuIn[3]);
	// ABE
	myMatrixMul<<< grid, block >>>(N, cuTmp[3], cuTmp[0], cuIn[4]);
	// CDF
	myMatrixMul<<< grid, block >>>(N, cuTmp[4], cuTmp[1], cuIn[5]);
	// AB+CD
	myMatrixAdd<<< grid, block >>>(N, cuTmp[0], cuTmp[1]);
	// ABE+CDF
	myMatrixAdd<<< grid, block >>>(N, cuTmp[3], cuTmp[4]);

	cudaMemcpy( IN[0], cuTmp[0], sizeof(uint32_t)*N*N, cudaMemcpyDeviceToHost);
	cudaMemcpy( IN[1], cuTmp[3], sizeof(uint32_t)*N*N, cudaMemcpyDeviceToHost);

    printf("%u\n", signature(N, IN[0]));
    printf("%u\n", signature(N, IN[1]));

	for (int i=0; i<6; i++)
		cudaFree(cuIn[i]);
	for (int i=0; i<4; i++)
		cudaFree(cuTmp[i]);
    return 0;
}
