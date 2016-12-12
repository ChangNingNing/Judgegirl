#include <stdio.h>
#include <stdlib.h>

int A[2][10] = {0};
int n;

int compare(const void *a, const void *b){
	return (*(int *)a)-(*(int *)b);
}

void swap(int *x, int *y){
	if(x==y) return;
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
	return;
}

void permutation(int index, int B[]){
	if(index==n){
		for(int i=0; i<n; i++){
			if(i!=0) printf(" ");
			printf("%d", B[i]);
		}
		printf("\n");
	}
	for(int i=0; i<n; i++){
		if(A[1][i]) continue;
		B[index] = A[0][i];
		A[1][i] = 1;
		permutation(index+1, B);
		A[1][i] = 0;
	}
	return;
}

int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", &A[0][i]);
	qsort((void *)A[0], n, sizeof(A[0][0]), compare);
	int B[10] = {0};
	permutation(0, B);
	return 0;
}
