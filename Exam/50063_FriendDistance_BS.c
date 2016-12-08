#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char A[16][16] = {0};
int N, M;
int bound = INT_MAX;
int isUse[16] = {0};
int ordering[16] = {0};
int ans[16] = {0};

int Ordering(int index, int dist, int constrain){
	if(index > N){
		if(dist > constrain) return 0;
		if(dist < bound){
			bound = dist;
			for(int i=1; i<=N; i++) ans[i] = ordering[i];
		}
		//if(dist <= constrain) return 1;
		return 1;
	}
	if(dist >= bound) return 0;
	if(dist > constrain) return 0;

	for(int i=0; i<N; i++){
		if(isUse[i]) continue;
		int tmpDist = dist, rest = 0;
		for(int j=0; j<N; j++){
			if(A[i][j]){
				if(isUse[j]==0) rest++;
				else if(index - isUse[j] > tmpDist) tmpDist = index - isUse[j];
			}
		}
		if(rest >= bound || rest > constrain) continue;

		isUse[i] = index;
		ordering[index] = i;
		if(Ordering(index+1, tmpDist, constrain)) return 1;
		isUse[i] = 0;
	}
	return 0;
}

int BS(int l, int r){
	memset(isUse, 0, sizeof(isUse));
	if(l > r) return l;
	int m = (l + r)/2;
	if(Ordering(1, 0, m))
		return BS(l, bound-1);
	else
		return BS(m+1, r);
}

int main(){
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++){
		char x[2], y[2];
		scanf("%s %s", x, y);
		int a = x[0]-'A', b = y[0]-'A';
		A[a][b] = A[b][a] = 1;
	}
	printf("%d\n", BS(0, N-1));
	for(int i=1; i<=N; i++) printf("%c%c", ans[i]+'A', (i!=N)? ' ': '\n');
	return 0;
}
