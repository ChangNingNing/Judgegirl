#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int M[6][6] = {0};
int x, y;

int isWin(){
	for(int i=1; i<=4; i++){
		for(int j=1; j<=4; j++){
			if(M[i][j] != ((i-1)*4 + j) % 16) return 0;
		}
	}
	return 1;
}

int main(){
	memset(M, -1, sizeof(M));
	for(int i=1; i<=4; i++){
		for(int j=1; j<=4; j++){
			scanf("%d", &M[i][j]);
			if(M[i][j]==0) x = i, y = j;
		}
	}

	int n;
	int flag = 0;
	while(scanf("%d", &n)==1 && n && !flag){
		int tmpX, tmpY;
		if(n < 0 || n > 15) continue;
		if(M[x+1][y]==n) tmpX = x+1, tmpY = y;
		else if(M[x-1][y]==n) tmpX = x-1, tmpY = y;
		else if(M[x][y+1]==n) tmpX = x, tmpY = y+1;
		else if(M[x][y-1]==n) tmpX = x, tmpY = y-1;
		else continue;
		
		M[x][y] = n;
		M[tmpX][tmpY] = 0;
		x = tmpX, y = tmpY;
		if(isWin()) flag = n;
	}

	for(int i=1; i<=4; i++){
		for(int j=1; j<=4; j++)
			printf("%d%c", M[i][j], (j==4? '\n': ' '));
	}
	if(flag) printf("1 %d\n", flag);
	else printf("0\n");
	return 0;
}
