#include "bingo.h"
#include <stdio.h>
#include <stdlib.h>

//const unsigned long long int table[4] = {0xff, 0x0101010101010101, 0x8040201008040201, 0x0102040810204080};

int bingo(const unsigned long long int *board, int *rowColumn){
	for(int i=7; i>=0; i--){
		if(((*board>>(i<<3)) & 0xff) == 0xff){
			*rowColumn = 7 - i;
			return 1;
		}
	}
	for(int i=7; i>=0; i--){
		if(((*board>>i) & 0x0101010101010101) == 0x0101010101010101){
			*rowColumn = 7 - i;
			return 2;
		}
	}
	if((*board & 0x8040201008040201) == 0x8040201008040201){
		*rowColumn = 0;
		return 3;
	}
	if((*board & 0x0102040810204080) == 0x0102040810204080){
		*rowColumn = 1;
		return 3;
	}
	return 0;
}
