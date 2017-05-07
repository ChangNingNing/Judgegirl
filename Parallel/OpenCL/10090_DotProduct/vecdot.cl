#define CHUNK 128
typedef unsigned int uint32_t;

uint32_t rotate_left(uint32_t x, uint32_t n){
	return (x << n) | (x >> (32-n));
}

uint32_t encrypt(uint32_t m, uint32_t key){
	return (rotate_left(m, key & 31) + key) ^ key;
}

__kernel void myDot(__global int *C, uint32_t N, uint32_t nT, uint32_t key1, uint32_t key2){
	int tid = get_global_id(0);
	int index = tid * CHUNK;
	int bound = (index + CHUNK < N)? index + CHUNK: N;
	uint32_t sum = 0;
	for (int i=index, j=0; i<bound; i++, j++){
		sum += encrypt(i, key1) * encrypt(i, key2);
	}
	C[tid] = sum;

	barrier(CLK_LOCAL_MEM_FENCE);

	for (int i=1; i<nT; i<<=1){
		if ((tid & ((i<<1)-1)) == 0){
			C[tid] += C[tid + i];
			if (tid <= 256)
				printf("tid = %d, i = %d, nT = %d\n", tid, i, nT);
		}
		barrier(CLK_LOCAL_MEM_FENCE);
	}
}
