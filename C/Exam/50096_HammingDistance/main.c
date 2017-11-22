#include <stdio.h>
#include <stdint.h>

uint8_t code[24];

int main(){
	int N, M, P;
	scanf("%d %d %d", &N, &M, &P);
	int n = 0;
	for (int i=0; i<M; i++){
		uint64_t _t;
		scanf("%llu", &_t);
		for (int j=1; j<=8 && n<N; j++)
			code[n++] = (uint8_t)((_t >> (64 - (j<<3))) & 255);
	}

	for (int i=0; i<P; i++){
		uint8_t _t;
		scanf("%hhu", &_t);
		for (int i=0; i<N; i++){
			uint32_t _tt = _t ^ code[i];
			int n = __builtin_popcount(_tt);
			if (n <= 1){
				printf("%hhu\n", code[i]);
				break;
			}
		}
	}
	return 0;
}
