#include <stdio.h>
#include <stdlib.h>

int A[2][102][102] = {0};
int alive[102][102] = {0};
int max = -1;
int maxX, maxY;

int Count(int x, int y, int index){
	int c = 0;
	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){
			if(A[index][x+i][y+j] && !(i==0 && j==0)) c++;
		}
	}
	return c;
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	int index = 0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d", &A[index][i][j]);
			if(A[index][i][j]){
				alive[i][j]++;
			}
		}
	}
	
	while(k--){
		int new = (index+1)%2;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				int c = Count(i, j, index);
				if(A[index][i][j]){
					if(c<2) A[new][i][j] = 0;
					else if(c<=3){
						A[new][i][j] = 1;
						alive[i][j]++;
					}
					else A[new][i][j] = 0;
				}
				else{
					if(c==3){
						A[new][i][j] = 1;
						alive[i][j]++;
					}
					else A[new][i][j] = 0;
				}
			}
		}
		index = new;
	}

	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(j!=1) printf(" ");
			printf("%d", A[index][i][j]);
			if(alive[i][j] >= max){
				max = alive[i][j];
				maxX = i;
				maxY = j;
			}
		}
		printf("\n");
	}
	printf("%d %d", maxX, maxY);
	return 0;
}
