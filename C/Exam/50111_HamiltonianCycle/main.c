#include <stdio.h>

#define MAXN 1001
char Adj[MAXN][MAXN];
int L[MAXN];
int N, E;

int DFS(int index, int pre, int begin){
	if (index >= N){
		if (!Adj[pre][0]) return 0;
		L[pre] = -1;
		return 1;
	}
	for (int p=-1, c=begin; c!=-1; p=c, c=L[c]){
		if (!Adj[pre][c]) continue;
		if (c == begin){
			if (DFS(index+1, c, L[c])){
				L[pre] = c;
				return 1;
			}
		}
		else {
			L[p] = L[c];
			if (DFS(index+1, c, begin)){
				L[pre] = c;
				return 1;
			}
			L[p] = c;
		}
	}
	return 0;
}

int main(){
	scanf("%d %d", &N, &E);
	for (int i=0; i<E; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		Adj[a][b] = Adj[b][a] = 1;
	}
	for (int i=0; i<N; i++)
		L[i] = i+1;
	L[N-1] = -1;

	if (!DFS(1, 0, 1))
		printf("NO SOLUTION\n");
	else {
		for (int c=0; c!=-1; c=L[c])
			printf("%d ", c);
		printf("0\n");
	}
	return 0;
}
