#include <stdio.h>
#include <string.h>

#define MAXN 16

int Adj[MAXN][MAXN];
int isU[MAXN];
int N, M;
int bound;

void myAssign(int index, int dist){
	if (index > N){
		if (dist < bound)
			bound = dist;
		return;
	}
	if (dist >= bound)
		return;

	for (int i=0; i<N; i++){
		if (isU[i]) continue;
		int tmp = dist, rest = 0;
		for (int j=0; j<N; j++){
			if (Adj[i][j]){
				if (isU[j] == 0)
					rest++;
				else
					tmp += index - isU[j];
			}
		}
		if ((((rest + 1)*rest)>>1) + tmp >= bound)
			return;//continue;
		isU[i] = index;
		myAssign(index+1, tmp);
		isU[i] = 0;
	}
	return;
}

int main(){
	scanf("%d %d", &N, &M);
	for (int i=0; i<M; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		Adj[a][b] = Adj[b][a] = 1;
	}

	bound = N * M;
	myAssign(1, 0);
	printf("%d\n", bound);
	return 0;
}
