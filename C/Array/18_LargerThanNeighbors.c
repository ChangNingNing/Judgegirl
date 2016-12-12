#include <stdio.h>
#include <stdlib.h>

int A[102][102] = {0};

int main(){
	int row, column, i, j;
	scanf("%d %d", &row, &column);
	for(i=1; i<=row; i++){
		for(j=1; j<=column; j++){
			scanf("%d", &A[i][j]);
		}
	}
	for(i=1; i<=row; i++){
		for(j=1; j<=column; j++){
			if(A[i][j]>A[i-1][j] && A[i][j]>A[i+1][j] && A[i][j]>A[i][j-1] && A[i][j]>A[i][j+1]){
				printf("%d\n", A[i][j]);
				j++;
			}
		}
	}
	return 0;
}