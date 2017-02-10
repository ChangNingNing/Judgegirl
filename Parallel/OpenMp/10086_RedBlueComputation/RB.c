#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <omp.h>

#define MAXN 1024
char T[2][MAXN][MAXN] = {0};

int main(){
	int N, M;
	assert(scanf("%d %d", &N, &M)==2);
	for(int i=0; i<N; i++){
		char tmp[MAXN];
		scanf("%s", tmp);
		for(int j=0; j<N; j++){
			if(tmp[j]=='R') T[0][i][j] = 1;
			else if(tmp[j]=='B') T[0][i][j] = 2;
		}
	}

	for(int r=0; r<M; r++){
		#pragma omp parallel
		{
			// Move Red
			#pragma omp for
			for(int i=0; i<N; i++)
				memset(T[1][i], 0, sizeof(char)*N);
			#pragma omp for
			for(int i=0; i<N; i++){
				for(int j=0; j<N; j++){
					if(T[0][i][j]==1){
						int next = (j+1) % N;
						if(T[0][i][next]==0) T[1][i][next] = 1;
						else T[1][i][j] = 1;
					}
					else if(T[0][i][j]==2) T[1][i][j] = 2;
				}
			}
	
			// Move Blue
			#pragma omp for
			for(int i=0; i<N; i++)
				memset(T[0][i], 0, sizeof(char)*N);
			#pragma omp for
			for(int i=0; i<N; i++){
				for(int j=0; j<N; j++){
					if(T[1][i][j]==2){
						int next = i!=N-1? i+1: 0;
						if(T[1][next][j]==0) T[0][next][j] = 2;
						else T[0][i][j] = 2;
					}
					else if(T[1][i][j]==1) T[0][i][j] = 1;
				}
			}
		}
	}

	for(int i=0; i<N; i++, puts(""))
		for(int j=0; j<N; j++)
			printf("%c", T[0][i][j]==0? 'W': T[0][i][j]==1? 'R': 'B');
	return 0;
}
