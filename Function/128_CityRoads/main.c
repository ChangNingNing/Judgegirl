#include <stdio.h>
#include <stdlib.h>
#include "intersection.h"

int main(){
	int map[100][100];
	int result[4];
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			scanf("%d", &(map[i][j]));
		}
	}
	intersection(map, result);
	for(int i=0; i<4; i++) printf("%d\n", result[i]);
	return 0;
}
