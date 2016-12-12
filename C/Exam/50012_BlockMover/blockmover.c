#include "blockmover.h"
#include <stdio.h>
#include <stdlib.h>
#define likely(x) __builtin_expect(!!(x),1)
#define unlikely(x) __builtin_expect(!!(x),0)

inline void printBlock(unsigned long long int *block){
	for(int i=0; i<64; i++){
		printf("%llu", (*block >> i) & 1);
		if((i & 7) == 7) puts("");
	}
	return;
}

inline void initialize(unsigned long long int *block, int row, int column, int size){
	static unsigned long long int mask[9] = {0, 0x1LLU, 0x303LLU, 0x70707LLU, 0xF0F0F0FLLU, 0x1F1F1F1F1FLLU, 0x3F3F3F3F3F3FLLU, 0x7F7F7F7F7F7F7FLLU, 0xFFFFFFFFFFFFFFFFLLU};
	*block = mask[size] << ((row << 3) | column);
	return;
}

inline int moveLeft(unsigned long long int *block){
	const unsigned long long int mask = 0x0101010101010101LLU;
	if(unlikely(*block & mask)) return 0;
	*block >>= 1;
	return 1;
}

inline int moveRight(unsigned long long int *block){
	const unsigned long long int mask = 0x8080808080808080LLU;
	if(unlikely(*block & mask)) return 0;
	*block <<= 1;
	return 1;
}

inline int moveUp(unsigned long long int *block){
	const unsigned long long int mask = 0xffLLU;
	if(unlikely(*block & mask)) return 0;
	*block >>= 8;
	return 1;
}

inline int moveDown(unsigned long long int *block){
	const unsigned long long int mask = 0xff00000000000000LLU;
	if(unlikely(*block & mask)) return 0;
	*block <<= 8;
	return 1;
}
