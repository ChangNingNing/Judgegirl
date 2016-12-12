#include <stdio.h>
#include <stdlib.h>

long long int input[1001][2] = {0}; /* 0 for dex., 1 for bit.*/

int compare(const void *a, const void *b){
	long long int intX = *(long long int *)a;
	long long int intY = *(long long int *)b;
	long long int bitX = *((long long int *)(a + sizeof(input[0][0])));
	long long int bitY = *((long long int *)(b + sizeof(input[0][0])));

	if(bitX != bitY) return bitX - bitY;
	else{
		long long int tmp = intX - intY;
		if(tmp > 0) return 1;
		else if(tmp == 0) return 0;
		return -1;
	}
}

int main(){
	int num = 0;
	while(scanf("%lld", &input[num][0])!=EOF){
		for(int i=0; i<63; i++){
			if((input[num][0]>>i)&1) input[num][1]++;
		}
		num++;
	}

	qsort((void *)input, num, sizeof(input[0]), compare);

	for(int i=0; i<num; i++){
		printf("%lld\n", input[i][0]);
	}
	return 0;
}
