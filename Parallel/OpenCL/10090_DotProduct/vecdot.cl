#define CHUNK 1024
#define threads 256
typedef unsigned int uint32_t;

uint32_t rotate_left(uint32_t x, uint32_t n){
	return (x << n) | (x >> (32-n));
}

uint32_t encrypt(uint32_t m, uint32_t key){
	return (rotate_left(m, key & 31) + key) ^ key;
}

__kernel void myDot(__global int *C, uint32_t N, uint32_t key1, uint32_t key2){
	int id = get_global_id(0);
	int gid = get_group_id(0);
	int lid = get_local_id(0);
	int index = id * CHUNK;
	int bound = (index + CHUNK < N)? index + CHUNK: N;
	__local uint32_t localC[threads];
	uint32_t sum = 0;
	for (int i=index; i<bound; i++)
		sum += encrypt(i, key1) * encrypt(i, key2);
	localC[lid] = sum;

	barrier(CLK_LOCAL_MEM_FENCE);

	int rest = threads;
	for (int rest=threads; rest>1; rest>>=1){
		int offset = (rest + 1) >> 1;
		if (lid + offset < rest)
			localC[lid] += localC[lid + offset];
		barrier(CLK_LOCAL_MEM_FENCE);
	}

	if (lid == 0)
		C[gid] = localC[0];
}
