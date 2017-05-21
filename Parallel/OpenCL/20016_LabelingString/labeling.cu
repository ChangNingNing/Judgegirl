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
#define LOGT 8
#define SeqSize 4

__global__ void myCudaCount(const char *text, int *pos, int n){
	int bid = blockIdx.x;
	int left = (blockIdx.y == 1)? bid * blockDim.x + ThreadSize/2: bid * blockDim.x;
	int tid = threadIdx.x;
	int id = left + tid;

	__shared__ int BIT[ThreadSize][LOGT];
	__shared__ int iBIT[ThreadSize];
	int seqIndex = id * SeqSize;
	int seq[SeqSize];

	if (seqIndex < n){
		// Transform
		int count = 1;
		for (int i=0; i<SeqSize; i++, count++){
			if (seqIndex + i < n){
				if (text[seqIndex + i] <= ' ')
					count = 0;
			}
			else{
				count = 0;
			}
			seq[i] = count;
		}

		iBIT[tid] = SeqSize - 1 - seq[SeqSize - 1];
		BIT[tid][0] = seq[SeqSize - 1] / SeqSize;
		__syncthreads();

		// Build tree
		int before = BIT[tid][0];
		for (int i=1, offset=1; i<LOGT; i++, offset <<= 1){
			int tmp = tid - offset;
			if (tmp >= 0){
				if (before != 0 && BIT[tmp][i-1] != 0)
						before = (BIT[tid][i] = before + BIT[tmp][i-1]);
				else
						before = (BIT[tid][i] = 0);
			}
			else
				BIT[tid][i] = before;
			__syncthreads();
		}

		// Set
		int offset = tid - 1;
		for (int i=LOGT-1; i>=0 && offset>=0; i--)
			offset -= BIT[offset][i];

		if (offset >= 0) offset = (left + offset) * SeqSize + iBIT[offset];

		if (tid >= ThreadSize/2 || id < ThreadSize / 2){
			for (int i=0; i<SeqSize && seqIndex+i<n; i++){
				if (seq[i] == 0)
					offset = seqIndex + i;
				pos[seqIndex + i] = seqIndex + i - offset;
			}
		}
	}
}
 
void labeling(const char *text, int *pos, int text_size)
{
	dim3 grid(CeilDiv( CeilDiv(text_size, SeqSize), ThreadSize), 2), block(ThreadSize, 1);
	myCudaCount<<< grid, block>>>(text, pos, text_size);
}
