#include <stdio.h>
#include <stdlib.h>

int B[200001] = {0};

int main(){
	int N, M, i;
	scanf("%d", &N);
	int A[N];
	for(i=0; i<N; i++) scanf("%d", &A[i]);
	scanf("%d", &M);

	for(i=0; i<N; i++)
		B[A[i] % M]++;
	for(i=0; i<M; i++) printf("%d\n", B[i]);
	return 0;
}