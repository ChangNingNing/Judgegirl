#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long A[1024][512>>6] = {0};

int main(){
	int N, M;
	while(scanf("%d %d", &N, &M)!=EOF){
		memset(A, 0, sizeof(A));
		int S = 0;
		int range = ((M-1)>>6) + 1;
		for(int k=0; k<N; k++){
			char tmp[515];
			scanf("%s", tmp);
			for(int i=0; i<range; i++){
				for(int j=0; j<64 && (i<<6)+j<M; j++){
					A[k][i] = (A[k][i] << 1) + (tmp[(i<<6)+j]-'0');
				}
			}
		}
		
		unsigned long long tmpC;
		unsigned long long tmpU;
		int con, uni;
		for(int i=0; i<N; i++){
			for(int j=i+1; j<N; j++){
				con = uni = 0;
				for(int k=0; k<range; k++){
					tmpC = A[i][k] & A[j][k];
					tmpU = A[i][k] | A[j][k];
					con += __builtin_popcountll(tmpC);
					uni += __builtin_popcountll(tmpU);
					/*
					int k_5 = k<<5;
					for(int l=0; l<32 && k_5+l<M; l++){
						con += (tmpC & 1);
						uni += (tmpU & 1);
						tmpC = tmpC >> 1;
						tmpU = tmpU >> 1;
					}
					*/
				}
				float similar = (float)con/uni;
				if(similar>=0.8) S++;
			}
		}
		printf("%.2f\n", (float)(S*100)/(N*(N-1)/2));
	}
	return 0;
}
