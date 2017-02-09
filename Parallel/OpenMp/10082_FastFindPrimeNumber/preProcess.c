#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define UINT unsigned int
#define offset 5
#define bit 31
#define MAXN ((1ULL<<31) >> offset)
#define SET(x) (T[(x) >> offset] |= 1ULL<<((x) & bit))
#define GET(x) ((T[(x) >> offset]>>((x) & bit))&1)

UINT T[MAXN] = {0};

void preSeive(int L, int R){
	int bound = sqrt(R);
	#pragma omp parallel
	for(int i=2; i<=bound; i++){
		if(!GET(i)){
			int _l = L / i * i;
			_l += i;
			if(_l==i) _l += i;
			#pragma omp for
			for(UINT j=_l; j<=R; j+=i)
				#pragma omp atomic
				T[j >> offset] |= 1ULL <<(j & bit);
		}
	}
}

int main(){
	SET(0);
	SET(1);
	int L=0, R=sqrt(2147483647);
	preSeive(L, R);
	printf("int P[] = { ");
	int sum = 0;
	for(int i=0; i<R; i++){
		if(!GET(i)){
			printf(", %d", i);
			sum++;
		}
	}
	printf("};\n");
	printf("sum = %d\n", sum);
	return 0;
}
