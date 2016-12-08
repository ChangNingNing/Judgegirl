#include "snake.h"
#include <stdlib.h>
#include <stdio.h>
int compare(const void *a, const void *b){
	int c = **(int **)a;
	int d = **(int **)b;
	return c-d;
}

void snake(const int *ptr_array[100][100], int m){
	const int *buffer[10000];
	int index = 0;
	for(int i=0; i<m; i++){
		if(i&1){
			for(int j=m-1; j>=0; j--){
				buffer[index] = ptr_array[i][j];
				index++;
			}
		}
		else{
			for(int j=0; j<m; j++){
				buffer[index] = ptr_array[i][j];
				index++;
			}
		}
	}

	qsort((void *) buffer, m*m, sizeof(buffer[0]), compare);
	index = 0;
	for(int i=0; i<m; i++){
		if(i&1){
			for(int j=m-1; j>=0; j--){
				ptr_array[i][j] = buffer[index];
				index++;
			}
		}
		else{
			for(int j=0; j<m; j++){
				ptr_array[i][j] = buffer[index];
				index++;
			}
		}
	}
}
