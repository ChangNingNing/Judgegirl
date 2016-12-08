#include "SpiralSnake.h"
#include <stdio.h>

#define MAXLEN 1000
int A[MAXLEN][MAXLEN];
int dirXY[2][4] = {0, -1, 0, 1,
		-1, 0, 1, 0};

void SpiralSnake(int N, int *snake, int *result){
	int x, y;
	int dir = 0, flag = 0;
	int changeCount = 1, tmpCC = 1;
	x = y = N/2;
	result[x*N + y] = snake[0];
	for(int i=1; i< N*N; i++){
		x += dirXY[0][dir];
		y += dirXY[1][dir];
		result[x*N + y] = snake[i];
		tmpCC--;
		if(tmpCC == 0){
			dir = (dir + 1) % 4;
			if(flag==0)
				tmpCC = changeCount, flag++;
			else
				tmpCC = ++changeCount, flag = 0;
		}
	}
	return;
}
