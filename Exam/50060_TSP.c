#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXN 16

int N;
int D[MAXN][MAXN] = {0};
int bound = INT_MAX;
int isUsed[MAXN] = {0};
int line[MAXN] = {0};

void TSP(int index, int dist){
	if(index >= N){
		dist += D[line[N-1]][0];
		if(dist < bound) bound = dist;
		return;
	}
	if(dist >= bound) return;
	
	for(int i=1; i<N; i++){
		if(isUsed[i]) continue;
		isUsed[i] = 1;
		line[index] = i;
		TSP(index + 1, dist + D[line[index-1]][i]);
		isUsed[i] = 0;
	}
	return;
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++) scanf("%d", &D[i][j]);
	isUsed[0] = 1;
	TSP(1, 0);
	printf("%d\n", bound);
	return 0;
}
