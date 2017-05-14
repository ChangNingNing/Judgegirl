#define CHUNK 1024
#define threads 256
#define AtomicMask 0x7

#define DOT { sum += encrypt(i, key1) * encrypt(i, key2), i++; }
#define UNROLL2  {DOT DOT}
#define UNROLL4  {UNROLL2 UNROLL2}
#define UNROLL8  {UNROLL4 UNROLL4}
#define UNROLL16 {UNROLL8 UNROLL8}

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

	int i;
	for (i=index; i+15<bound; ){
		UNROLL16;
	}
	while (i < bound){
		DOT;
	}

	localC[lid] = sum;

	atomic_add( &(C[lid & AtomicMask]), localC[lid]);
}
