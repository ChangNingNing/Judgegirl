#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int W[1024], DP[1024];
int L[1024][1024], R[1024][1024];

int main(){
	int N, M;
	while (scanf("%d %d", &N, &M)==2){
		for (int i=0; i<N; i++)
			scanf("%d", &W[i]);
//		for (int i=0; i<N; i++){
//			L[i][i] = 0;
//			for (int j=i+1; j<N; j++)
//				L[i][j] = L[i][j-1] + W[j]*(j-i);
//		}
//		for (int i=N-1; i>=0; i--){
//			R[i][i] = 0;
//			for (int j=i-1; j>=0; j--)
//				R[i][j] = R[i][j+1] + W[j]*(i-j);
//		}

		for(int i=0; i<N; i++)
			DP[i] = R[i][0];

		for (int i=1; i<M; i++){
			for (int j=N-M+i; j>=i; j--){
				int min = INT_MAX;
				for (int k=j-1; k>=i-1; k--){
					int mid = (j + k) / 2;
					int tmp = DP[k] + L[k][mid] + R[j][mid+1];
					if (tmp < min) min = tmp;
				}
				DP[j] = min;
			}
		}
		int min = INT_MAX;
		for (int i=M-1; i<N; i++){
			int tmp = DP[i] + L[i][N-1];
			if (tmp < min) min = tmp;
		}
		printf("%d\n", min);
	}
	return 0;
}
