#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char A[16][16] = {0};
int N, M;
int bound = INT_MAX;
int isUse[16] = {0};
int ordering[16] = {0};
int ans[16] = {0};

void Ordering(int index, int dist){
	if(index>N){
		if(dist < bound){
			bound = dist;
			for(int i=1; i<=N; i++) ans[i] = ordering[i];
		}
		return;
	}
	for(int i=0; i<N; i++){
		if(isUse[i]) continue;
		int tmpDist = dist;
		for(int j=1; j<index; j++){
			if(A[ordering[j]][i])
				if(index - j > tmpDist) tmpDist = index - j;
		}
		isUse[i] = index;
		ordering[index] = i;
		Ordering(index+1, tmpDist);
		isUse[i] = 0;
	}
	return;
}

int main(){
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++){
		char x[2], y[2];
		scanf("%s %s", x, y);
		int a = x[0]-'A', b = y[0]-'A';
		A[a][b] = A[b][a] = 1;
	}
	Ordering(1, 0);
	printf("%d\n", bound);
	for(int i=1; i<=N; i++) printf("%c%c", ans[i]+'A', (i!=N)? ' ': '\n');
	return 0;
}
