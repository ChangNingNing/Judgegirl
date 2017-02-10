#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAXN 10001
#define MAXM 1000001
#define Swap(A, B) { int t=A; A=B; B=t;}

int DP[2][MAXM] = {0};
int obj[MAXN][2] = {0};

int Max(int a, int b) { return a>b? a: b; }

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++)
		scanf("%d %d", &obj[i][0], &obj[i][1]);

	int pre = 0, cur = 1;
	for(int i=0; i<N; i++){
		int w = obj[i][0], v = obj[i][1];
		#pragma omp parallel
		{
			#pragma omp for
			for(int j=w; j<=M; j++)
				DP[cur][j] = Max(DP[pre][j], DP[pre][j-w] + v);
			#pragma omp for
			for(int j=1; j<w; j++)
				DP[cur][j] = DP[pre][j];
		}
		Swap(pre, cur);
	}
	printf("%d\n", DP[pre][M]);
	return 0;
}
