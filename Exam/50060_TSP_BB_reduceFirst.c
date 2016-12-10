#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MAXN 16

int N, ub = INT_MAX, minReturn = INT_MAX;
int inUsed[MAXN] = {0}, D[MAXN][MAXN] = {0};

int myReduce(){
	int reduce = 0, min;
	for(int i=0; i<N; i++){
		min = INT_MAX;
		for(int j=0; j<N; j++){
			int tmp = D[i][j];
			if(tmp >= 0 && tmp < min) min = tmp;
		}
		for(int j=0; j<N; j++) D[i][j] -= min;
		reduce += min;
	}	
	for(int j=0; j<N; j++){
		min = INT_MAX;
		for(int i=0; i<N; i++){
			int tmp = D[i][j];
			if(tmp >= 0 && tmp < min) min = tmp;
		}
		for(int i=0; i<N; i++) D[i][j] -= min;
		reduce += min;
	}
	return reduce;
}

void BB(int index, int lb, int pre){
	if(lb >= ub) return;
	if(index >= N){
		int cost = lb - minReturn + D[pre][0];
		if(cost < ub) ub = cost;
		return;
	}

	for(int k=1; k<N; k++){
		if(inUsed[k]) continue;
		inUsed[k] = 1;
		BB(index+1, lb+D[pre][k], k);
		inUsed[k] = 0;
	}
	return;
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++) scanf("%d", &D[i][j]);
		D[i][i] = -1;
	}
	int reduce = myReduce();
	for(int i=1; i<N; i++){
		if(D[i][0] < minReturn)
			minReturn = D[i][0];
	}
	BB(1, reduce + minReturn, 0);
	printf("%d\n", ub);
	return 0;
}
