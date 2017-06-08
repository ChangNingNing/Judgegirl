#include "labeling.h"
#include <cstdio>
#include <cassert>
#include <thrust/scan.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/device_ptr.h>
#include <thrust/execution_policy.h>

__device__ __host__ int CeilDiv(int a, int b) { return (a-1)/b + 1; }
__device__ __host__ int CeilAlign(int a, int b) { return CeilDiv(a, b) * b; }

#define ThreadSize 256
#define LOGT 4
#define SeqSize 4

__global__ void myCudaCount(const char *text, int *pos, int n){
	int left = blockIdx.x * blockDim.x;
	int tid = threadIdx.x;
	int id = left + tid;

	__shared__ int BIT[ThreadSize][LOGT+1];
	__shared__ int iBIT[ThreadSize];
	int seqIndex = id * SeqSize;
	int seq[SeqSize];

	if (seqIndex < n){
		// Transform
		for (int i=0, count=1; i<SeqSize; i++, count++){
			if (seqIndex + i < n){
				if (text[seqIndex + i] <= ' ')
					count = 0;
			}
			else
				count = 0;
			seq[i] = count;
		}

		iBIT[tid] = SeqSize - 1 - seq[SeqSize - 1];
		BIT[tid][0] = seq[SeqSize - 1];
		__syncthreads();

		// Build tree
		for (int i=1, offset=1; i<=LOGT; i++, offset<<=2){
			int count = 0;
			for (int j=0, tmp = tid; j<SeqSize && tmp >= 0; j++, tmp-=offset){
				if (BIT[tmp][i-1] >= SeqSize) count++;
				else break;
			}
			BIT[tid][i] = count;
			__syncthreads();
		}

		// Set
		int offset = tid - 1;
		for (int i=LOGT, shift=64; i>0 && offset>=0; i--, shift>>=2)
			offset -= shift * BIT[offset][i];

		if (offset >= 0) offset = (left + offset) * SeqSize + iBIT[offset];
		else offset = left * SeqSize - 1;

		for (int i=0; i<SeqSize && seqIndex+i<n; i++){
			if (seq[i] == 0) offset = seqIndex + i;
			pos[seqIndex + i] = seqIndex + i - offset;
		}
	}
}

__global__ void myCudaFix(int *pos, int n){
	int left = (blockIdx.x+1) * ThreadSize * SeqSize;
	int tid = threadIdx.x * SeqSize;
	int seqIndex = left + tid;
	if (seqIndex < n){
		int prefix = pos[left - 1];
		if (prefix == 0) return;
		if (pos[seqIndex] > tid) pos[seqIndex] += prefix, seqIndex++, tid++;
		if (pos[seqIndex] > tid) pos[seqIndex] += prefix, seqIndex++, tid++;
		if (pos[seqIndex] > tid) pos[seqIndex] += prefix, seqIndex++, tid++;
		if (pos[seqIndex] > tid) pos[seqIndex] += prefix;
	}
}

void labeling(const char *text, int *pos, int text_size)
{
	uint32_t nGrid = CeilDiv( CeilDiv(text_size, SeqSize), ThreadSize);
	dim3 grid(nGrid, 1), block(ThreadSize, 1);
	myCudaCount<<< grid, block>>>(text, pos, text_size);

	dim3 grid2( nGrid-1, 1), block2(ThreadSize/2, 1);
	myCudaFix<<< grid2, block2>>>(pos, text_size);
}
