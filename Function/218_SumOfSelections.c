#include <stdio.h>
#include <stdlib.h>

int P[16][16] = {0};

void Pascal(int n){
	for(int i=0; i<16; i++) P[i][0] = 1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<16; j++){
			P[i][j] = P[i-1][j-1]+P[i-1][j];
			if(P[i][j]==0) break;
		}
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	int sum = 0;
	Pascal(n);
	for(int i=0; i<=m; i++){
		sum += P[n][i];
	}
	printf("%d", sum);
	return 0;
}
