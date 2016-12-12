#include <stdio.h>
#include <stdlib.h>

int A[101][101] = {0};

int main(){
	int row, column, i, j;
	scanf("%d %d", &row, &column);
	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			scanf("%d", &A[i][j]);
			A[row][j] += A[i][j];
		}
	}
	for(i=0; i<column; i++){
		A[row][i] /= row;
		printf("%d\n", A[row][i]);
	}
	return 0;
}