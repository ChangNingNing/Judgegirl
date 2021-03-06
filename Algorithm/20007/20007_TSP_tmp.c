#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MAXN 30

int N, ub = INT_MAX;
int outUsed[MAXN] = {0}, inUsed[MAXN] = {0}, D[MAXN][MAXN] = {0};

int myReduce(int X[MAXN], int Y[MAXN]){
	int reduce = 0, minX[N], minY[N];

	for(int i=0; i<N; i++) minX[i] = minY[i] = INT_MAX;
	for(int i=0; i<N; i++){
		if(outUsed[i]) continue;
		for(int j=0; j<N; j++){
			if(inUsed[j]) continue;
			int tmp = D[i][j] - X[i] - Y[j];
			if(tmp >= 0 && tmp < minX[i]) minX[i] = tmp;
		}
	}
	for(int i=0; i<N; i++){
		if(minX[i] >= INT_MAX) continue;
		reduce += minX[i];
		X[i] += minX[i];
	}
	
	for(int i=0; i<N; i++){
		if(outUsed[i]) continue;
		for(int j=0; j<N; j++){
			if(inUsed[j]) continue;
			int tmp = D[i][j] - X[i] - Y[j];
			if(tmp >= 0 && tmp < minY[j]) minY[j] = tmp;
		}
	}
	for(int i=0; i<N; i++){
		if(minY[i] >= INT_MAX) continue;
		reduce += minY[i];
		Y[i] += minY[i];
	}
	return reduce;
}

int compare(const void *a, const void *b){
	return *(int *)a - *(int *)b;
}

void BB(int index, int X[MAXN], int Y[MAXN], int lb, int pre){
	if(lb >= ub) return;
	if(index >= N){
		if(lb < ub) ub = lb;
		return;
	}

	int tmpX[N], tmpY[N];
	for(int k=1; k<N; k++){
		if(inUsed[k] || D[pre][k]<0) continue;
		int reduce = lb;
		reduce += D[pre][k] - X[pre] - Y[k];
		memcpy(tmpX, X, sizeof(tmpX));
		memcpy(tmpY, Y, sizeof(tmpY));
		inUsed[k] = 1;
		reduce += myReduce(tmpX, tmpY);
		outUsed[k] = 1;
		BB(index+1, tmpX, tmpY, reduce, k);
		inUsed[k] = outUsed[k] = 0;
	}
	return;
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			scanf("%d", &D[i][j]);
			if(D[i][j] == 0) D[i][j] = -1;
		}
	}
	int X[MAXN] = {0}, Y[MAXN] = {0};
	int reduce = myReduce(X, Y);
	outUsed[0] = 1;
	BB(1, X, Y, reduce, 0);
	printf("%d\n", ub);
	return 0;
}
