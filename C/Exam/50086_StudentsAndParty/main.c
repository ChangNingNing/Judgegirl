#include <stdio.h>
#define MAXN 32768
#define MAXK 256

int T[MAXN][MAXK];
int nT[MAXN];
int ans[MAXN];

int main(){
	int N, E;
	scanf("%d %d", &N, &E);
	for (int i=0; i<E; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		T[a][nT[a]] = b;
		T[b][nT[b]] = a;
		nT[a]++, nT[b]++;
	}

	int tmp;
	while (scanf("%d", &tmp)==1){
		ans[tmp] = 1;
		for (int i=0; i<nT[tmp]; i++)
			ans[T[tmp][i]] = 1;
	}

	for (int i=0; i<N; i++)
		if (!ans[i]) printf("%d\n", i);
	return 0;
}
