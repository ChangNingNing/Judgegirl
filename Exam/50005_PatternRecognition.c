#include <stdio.h>
#include <stdlib.h>

int A[11][11] = {0}, B[11][11] = {0};

int main(){
	int n, k, m, d;
	scanf("%d %d %d %d", &n, &k, &m, &d);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++) scanf("%d", &A[i][j]);
	}
	for(int i=1; i<=k; i++){
		for(int j=1; j<=k; j++) scanf("%d", &B[i][j]);	
	}
	int sumA[11][11] = {0};
	int sumB = 0;
	for(int i=1; i<=k; i++){
		for(int j=1; j<=k; j++) sumB += B[i][j];
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int kk=1; kk<=i; kk++){
				for(int l=1; l<=j; l++) sumA[i][j] += A[kk][l];
			}
		}
	}

	for(int i=n-k+1; i>=1; i--){
		for(int j=n-k+1; j>=1; j--){
			int nM = 0;
			for(int kk=0; kk<k; kk++){
				for(int l=0; l<k; l++){
					if(A[kk+i][l+j]!=B[kk+1][l+1]) nM++;
				}
			}
			int tmpA = sumA[i+k-1][j+k-1] - sumA[i+k-1][j-1] - sumA[i-1][j+k-1] + sumA[i-1][j-1];
			if((nM <= m) && (abs(tmpA - sumB)<=d)){
				printf("%d %d\n", i-1, j-1);
				return 0;
			}
		}
	}
	printf("-1 -1\n");
	return 0;
}
