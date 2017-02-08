#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <omp.h>

#define MAXN 2048
#define SIDE (MAXN + 2)
#define nLive(A, i, j) A[i][j-1]+A[i][j+1]+A[i-1][j-1]+A[i-1][j]+A[i-1][j+1]+A[i+1][j-1]+A[i+1][j]+A[i+1][j+1]

char T[2][SIDE][SIDE] = {0};
char input[SIDE][SIDE] = {0};

int main(){
	int N, M;
	assert(scanf("%d %d", &N, &M)==2);
	for(int i=1; i<=N; i++)
		scanf("%s", input[i]);
	#pragma omp parallel for
	for(int i=1; i<=N; i++)
		for(int j=0; j<N; j++)
			if(input[i][j] == '1') T[0][i][j+1] = 1;
	#pragma omp parallel
	for(int g=1; g<=M; g++){
		#pragma omp for
		for(int i=1; i<=N; i++){
			for(int j=1; j<=N; j++){
				int pre = (g-1) & 1, cur = g & 1;
				int nln = nLive(T[pre], i ,j);
				T[cur][i][j] = (T[pre][i][j]==0 && nln==3) || (T[pre][i][j]==1 && (nln==2 || nln==3));
				j++;
				nln = nLive(T[pre], i ,j);
				T[cur][i][j] = (T[pre][i][j]==0 && nln==3) || (T[pre][i][j]==1 && (nln==2 || nln==3));
				j++;
				nln = nLive(T[pre], i ,j);
				T[cur][i][j] = (T[pre][i][j]==0 && nln==3) || (T[pre][i][j]==1 && (nln==2 || nln==3));
				j++;
				nln = nLive(T[pre], i ,j);
				T[cur][i][j] = (T[pre][i][j]==0 && nln==3) || (T[pre][i][j]==1 && (nln==2 || nln==3));
			}
		}
	}

	int r = M & 1;
	#pragma omp parallel for
	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			if(T[r][i][j]==1) input[i][j-1] = '1';
			else input[i][j-1] = '0';
		}
		input[i][N] = '\0';
	}
	for(int i=1; i<=N; i++)
		puts(input[i]);
	return 0;
}
