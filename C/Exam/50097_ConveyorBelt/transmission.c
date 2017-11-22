#include "transmission.h"
#include <stdint.h>
#include <string.h>
#define MAXN 1048576

uint64_t tmp[MAXN];
void trans_lld(uint64_t *belt, int N, int T){
	if (T == 0) return;
	memcpy(tmp, belt, sizeof(uint64_t) * T);
	memcpy(belt, belt+T, sizeof(uint64_t) * (N-T));
	memcpy(belt+N-T, tmp, sizeof(uint64_t) * T);
	return;
}

void trans_bit(uint64_t *belt, int N, int T){
	if (T == 0) return;
	uint64_t _t = belt[0]>>(64-T);
	for (int i=0; i<N-1; i++)
		belt[i] = (belt[i] << T) | (belt[i+1] >> (64-T));
	belt[N-1] = (belt[N-1] << T) | _t;
	return;
}

void transmission(long long int belt[],int N,int T){
	trans_lld((uint64_t *)belt, N, (T >> 6) % N);
	trans_bit((uint64_t *)belt, N, (T & 63));
	return;
}
