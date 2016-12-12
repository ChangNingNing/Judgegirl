#include <stdio.h>
#include <stdlib.h>

int main(){
	int N, i;
	scanf("%d", &N);
	int even[N], odd[N];
	int evenN = 0, oddN = 0;
	for(i=0; i<N; i++){
		int tmp;
		scanf("%d", &tmp);
		if(tmp % 2)
			odd[oddN++] = tmp;
		else
			even[evenN++] = tmp;
	}

	for(i=0; i<oddN; i++){
		if(i) printf(" ");
		printf("%d", odd[i]);
	}
	printf("\n");
	for(i=0; i<evenN; i++){
		if(i) printf(" ");
		printf("%d", even[i]);
	}
	printf("\n");
}