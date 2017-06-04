#define CHUNK 512
#define threads 256
#define AtomicN 8
#define AtomicMask 0x7

#define DOT { sum += encrypt(i, key1[j]) * encrypt(i, key2[j]), i++; }
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

__kernel void myDot(
	__global int *C,
	__global uint32_t *N, __global uint32_t *key1, __global uint32_t *key2,
	uint32_t nCase
){
	int id = get_global_id(0);
	int gid = get_group_id(0);
	int lid = get_local_id(0);

	int index = id * CHUNK;
	int bound = index + CHUNK, _bound;
	int hash = lid & AtomicMask;
	uint32_t sum;

	int i, j;
	for (j=0; j<nCase; j++){
		if (bound < N[j]) _bound = bound;
		else _bound = N[j];
		sum = 0;

		for (i=index; i+15<_bound; ){
			UNROLL16;
		}
		while (i < _bound){
			DOT;
		}

		atomic_add( &(C[j*AtomicN + hash]), sum);
	}
}
