#include <stdio.h>
#include <stdlib.h>

int A[1000][10000] = {0};
int nA[1000] = {0};

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++){
		int temp;
		scanf("%d", &temp);
		A[temp%M][nA[temp%M]] = temp;
		nA[temp%M]++;
	}
	for(int i=0; i<M; i++){
		int sum = 0, max = 0, min = 10001;
		for(int j=0; j<nA[i]; j++){
			sum += A[i][j];
			if(A[i][j] > max) max = A[i][j];
			if(A[i][j] < min) min = A[i][j];
		}
		printf("%d %d %d\n", sum, max, min);
	}
	return 0;
}
