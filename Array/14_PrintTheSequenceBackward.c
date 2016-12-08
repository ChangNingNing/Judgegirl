#include <stdio.h>
#include <stdlib.h>

int main(){
	int N, i;
	int A[1001];
	scanf("%d", &N);
	for(i=0; i<N; i++) scanf("%d", &A[i]);
	for(i=N-1; i>=0; i--){
		printf("%d", A[i]);
		if(i) printf(" ");
	}
	printf("\n");
	return 0;
}