#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define MAXN 512
short A[MAXN][MAXN];
int B[MAXN][MAXN];
int C[MAXN][MAXN];

int main(){
	int Ah, Aw, Bh, Bw;
	while(scanf("%d %d %d %d", &Ah, &Aw, &Bh, &Bw)==4){
		for(int i=0; i<Ah; i++)
			for(int j=0; j<Aw; j++)
				scanf("%d", &A[i][j]);

		for(int i=0; i<Bh; i++)
			for(int j=0; j<Bw; j++)
				scanf("%d", &B[i][j]);

		int min = INT_MAX, minX, minY;
		#pragma omp parallel for
		for(int i=0; i<=Ah-Bh; i++)
			for(int j=0; j<=Aw-Bw; j++){
				int sum = 0;
				for(int k=0; k<Bh; k++){
					for(int l=0; l<Bw; l++){
						int tmp = A[i+k][j+l]-B[k][l];
						sum += tmp * tmp;
					}
				}
				C[i][j] = sum;
			}
		for(int i=0; i<=Ah-Bh; i++)
			for(int j=0; j<=Aw-Bw; j++)
				if(C[i][j] < min)
					min = C[i][j], minX = i, minY = j;
		printf("%d %d\n", minX+1, minY+1);				
	}
	return 0;
}
