#include <stdio.h>
#include <stdlib.h>

char A[128][128] = {0};
int L, X, Y;

int isCorrect(int x1, int y1, int x2, int y2){
	if(x2 >= Y || x2 < 0) return 0;
	if(y2 >= X || y2 < 0) return 0;
	if(x1 < 0 && y1 < 0) return 1;
	if(x1 != x2 && y1 != y2){
		int slope = (x2-x1)/(y2-y1);
		if(slope == 1 || slope == -1) return 1;
		return 0;
	}
	return 1;
}

int main(){
	scanf("%d %d %d", &L, &X, &Y);
	for(int i=1; i<=L; i++){
		int n, preX = -1, preY = -1, curX, curY;
		scanf("%d", &n)==1;
		for(int j=1; j<=n; j++){
			scanf("%d %d", &curX, &curY)==2;
			curY = X - 1 - curY;
			if(!isCorrect(preX, preY, curX, curY)){
				printf("ERROR %d %d\n", i, j);
				return 0;
			}
			if(preX < 0){
				preX = curX, preY= curY;
				continue;
			}
			int dirX = (curX-preX)!=0? (abs(curX-preX))/(curX-preX): 0;
			int dirY = (curY-preY)!=0? (abs(curY-preY))/(curY-preY): 0;
			while(preX!=curX || preY!=curY){
				A[preY][preX] = 1;
				preX += dirX;
				preY += dirY;
			}
			A[preY][preX] = 1;
		}
	}
	for(int i=0; i<X; i++, puts("")){
		for(int j=0; j<Y; j++)
			printf("%d", A[i][j]);
	}
	return 0;
}
