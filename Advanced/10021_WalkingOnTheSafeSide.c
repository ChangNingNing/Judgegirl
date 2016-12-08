#include <stdio.h>
#include <stdlib.h>

int A[101][101] = {0};
int N, M;

int main(){
	while(scanf("%d %d", &N, &M)!=EOF){
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				scanf("%d", &A[i][j]);
				if(A[i][j]) A[i][j] *= -1;
			}
		}
		if(A[0][0]==0) A[0][0] = 1;
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				if(A[i][j]<=0) continue;
				if(A[i+1][j]>=0) A[i+1][j] = (A[i+1][j]+A[i][j]) % 10000;
				if(A[i][j+1]>=0) A[i][j+1] = (A[i][j+1]+A[i][j]) % 10000;
			}
		}
		printf("%d\n", A[N-1][M-1]);
	}
	return 0;
}
