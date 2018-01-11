#include <stdio.h>
#include <string.h>

#define MAXN 16

int Adj[MAXN][MAXN];
int A[MAXN];
int isU[MAXN];
int N, M;
int bound;

void myAssign(int index, int dist){
	if (index == N){
		if (dist < bound)
			bound = dist;
		return;
	}
	if (dist >= bound)
		return;

	for (int i=0; i<N; i++){
		if (isU[i]) continue;
		int tmp = dist;
		for (int j=0; j<index; j++){
			if (Adj[i][A[j]])
				tmp += index - j;
		}
		isU[i] = 1;
		A[index] = i;
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
	myAssign(0, 0);
	printf("%d\n", bound);
	return 0;
}
