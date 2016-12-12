#include "snake.h"
#include <stdio.h>

int snake(int *ptr, int *row, int *column) {
	int i, j;
	for(i=0; ; i++) if(ptr[i]!=i) break;
	*column = i;
	int c = i;
	int flag = 1;
	for(i=1; ptr[c]!=0 && flag; i++){
		if(i&1){
			for(j=*column-1; j>=0; j--, c++){
				if(ptr[c] != i*(*column) + j){
					flag = 0;
					break;
				}
			}
		}
		else{
			for(j=0; j<*column; j++, c++){
				if(ptr[c] != i*(*column) + j){
					flag = 0;
					break;
				}
			}
		}
	}
	if(flag){
		*row = i;
		return 1;
	}
	else{
		*row = i-1;
		*column = j;
		return 0;
	}
}
