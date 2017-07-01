#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <thrust/execution_policy.h>
#include <thrust/reduce.h>

#define MAXN 16777216
#define ThreadSize 256
#define SeqSize 1024
#define atomicN ThreadSize

__device__ __host__ int CeilDiv(int a, int b) { return (a-1)/b + 1; }
__device__ __host__ uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
__device__ __host__ uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

#define DOT { sum += encrypt(i, key1) * encrypt(i, key2), i++; }
#define UNROLL2  {DOT DOT}
#define UNROLL4  {UNROLL2 UNROLL2}
#define UNROLL8  {UNROLL4 UNROLL4}
#define UNROLL16 {UNROLL8 UNROLL8}

__global__ void myDotProduct( uint32_t *cuC, int n, uint32_t key1, uint32_t key2){
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	int id = tid * SeqSize;
	int bound = (id + SeqSize < n)? id + SeqSize: n;

	uint32_t sum = 0;
	int i;
	for (i=id; i+15<bound; ){
		UNROLL16;
	}
	if (i+7 < bound) UNROLL8;
	if (i+3 < bound) UNROLL4;
	if (i+1 < bound) UNROLL2;
	while (i < bound) DOT;

	atomicAdd( &(cuC[tid % atomicN]), sum);
}

int main(int argc, char *argv[]) {
    int N;
    uint32_t key1, key2;
	uint32_t *cuC;
	cudaMalloc( &cuC, sizeof(uint32_t)*atomicN);
    while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {
		int chunk = CeilDiv(N, SeqSize);
		dim3 grid(CeilDiv(chunk, ThreadSize)), block(ThreadSize);

		cudaMemset( cuC, 0, sizeof(uint32_t)*atomicN);
		myDotProduct<<<grid, block>>>(cuC, N, key1, key2);
		uint32_t sum = thrust::reduce(thrust::device, cuC, cuC+atomicN);
        printf("%" PRIu32 "\n", sum);
    }
	cudaFree(cuC);
    return 0;
}
