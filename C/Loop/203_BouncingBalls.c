#include <stdio.h>
#include <stdlib.h>

int main(){
	int X, Y, x1, y1, x2, y2, dx1, dy1, dx2, dy2, sec;
	scanf("%d %d %d %d %d %d %d %d %d %d %d", &X, &Y, &x1, &y1, &x2, &y2, &dx1, &dy1, &dx2, &dy2, &sec);
	while(sec--){
		int tmpx1 = x1, tmpy1 = y1, tmpx2 = x2, tmpy2 = y2;
		tmpx1 += dx1;
		tmpy1 += dy1;
		tmpx2 += dx2;
		tmpy2 += dy2;
		if(x1==x2 && y1==y2){
			tmpx1 = tmpx1 ^ tmpx2;
			tmpx2 = tmpx1 ^ tmpx2;
			tmpx1 = tmpx1 ^ tmpx2;

			tmpy1 = tmpy1 ^ tmpy2;
			tmpy2 = tmpy1 ^ tmpy2;
			tmpy1 = tmpy1 ^ tmpy2;

			dx1 = dx1 ^ dx2;
			dx2 = dx1 ^ dx2;
			dx1 = dx1 ^ dx2;

			dy1 = dy1 ^ dy2;
			dy2 = dy1 ^ dy2;
			dy1 = dy1 ^ dy2;
		}
		if(x1==1 || x1==X){
			dx1 *= -1;
			tmpx1 = x1 + dx1;
		}
		if(y1==1 || y1==Y){
			dy1 *= -1;
			tmpy1 = y1 + dy1;
		}
		if(x2==1 || x2==X){
			dx2 *= -1;
			tmpx2 = x2 + dx2;
		}
		if(y2==1 || y2==Y){
			dy2 *= -1;
			tmpy2 = y2+ dy2;
		}
		x1 = tmpx1;
		x2 = tmpx2;
		y1 = tmpy1;
		y2 = tmpy2;
	}
	printf("%d\n", x1);
	printf("%d\n", y1);
	printf("%d\n", x2);
	printf("%d\n", y2);
	return 0;
}