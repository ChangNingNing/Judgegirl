#include <stdio.h>
#include <stdlib.h>

int W[17][17] = {0};
int P[17][17] = {0};

int h(int M){
	int sum = 0;
	for(int i=0; i<M; i++){
		for(int j=0; j<M; j++){
			sum += P[i][j]*W[i][j];
		}
	}
	if(sum >= 2*M*M) return 1;
	return 0;
}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++){
		for(int j=0; j<M; j++){
			W[i][j] = 1;
		}
	}
	while(N--){
		int isAC;
		scanf("%d", &isAC);
		for(int i=0; i<M; i++){
			for(int j=0; j<M; j++){
				scanf("%d", &P[i][j]);
			}
		}
		int isSatisfied = h(M);
		if(isSatisfied==isAC) continue;
		else{
			if(isAC){
				for(int i=0; i<M; i++){
					for(int j=0; j<M; j++){
						if(P[i][j]) W[i][j] *= 2;
					}
				}
			}
			else{
				for(int i=0; i<M; i++){
					for(int j=0; j<M; j++){
						if(P[i][j]){
							W[i][j] /= 2;
							if(W[i][j]<1) W[i][j] = 1;
						}
					}
				}
			}
		}
	}
	int Q;
	scanf("%d", &Q);
	while(Q--){
		for(int i=0; i<M; i++){
			for(int j=0; j<M; j++){
				scanf("%d", &P[i][j]);
			}
		}
		printf("%d\n", h(M));
	}
	return 0;
}
