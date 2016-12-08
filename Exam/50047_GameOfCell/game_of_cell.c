#include "game_of_cell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define size 52
int Count(char tmp[size][size], int x, int y){
	int num = 0;
	num += (tmp[x-1][y-1]>>1);
	num += (tmp[x-1][y]>>1);
	num += (tmp[x-1][y+1]>>1);
	num += (tmp[x][y-1]>>1);
	num += (tmp[x][y+1]>>1);
	num += (tmp[x+1][y-1]>>1);
	num += (tmp[x+1][y]>>1);
	num += (tmp[x+1][y+1]>>1);
	return num;
}

void game_of_cell(int grid[50][50], int outcome[50][50], int N){
	char tmp[2][size][size] = {0};
	int index = 0;
	int changeT[3][9]={ 0, 0, 0, 2, 0, 0, 0, 0, 0,
			    1, 1, 2, 1, 1, 1, 1, 1, 1,
			    0, 0, 2, 2, 1, 1, 1, 1, 1 };
	for(int i=1; i<=50; i++){
		for(int j=1; j<=50; j++){
			tmp[index][i][j] = grid[i-1][j-1];
		}
	}
	while(N--){
		int new = (index+1)%2;
		for(int i=1; i<=50; i++){
			for(int j=1; j<=50; j++){
				int nH = Count(tmp[index], i, j);
				tmp[new][i][j] = changeT[tmp[index][i][j]][nH];
			}
		}
		index = new;
	}
	for(int i=0; i<50; i++){
		for(int j=0; j<50; j++){
			outcome[i][j] = tmp[index][i+1][j+1];
		}
	}
	return;
}
