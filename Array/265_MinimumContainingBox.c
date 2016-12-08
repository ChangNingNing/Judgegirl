#include <stdio.h>
#include <stdlib.h>

int main(){
	int x, y;
	int minX = 10001, minY = 10001, maxX = -10001, maxY = -10001;
	while(scanf("%d %d", &x, &y)!=EOF){
		if(x<minX) minX = x;
		if(x>maxX) maxX = x;
		if(y<minY) minY = y;
		if(y>maxY) maxY = y;
	}
	printf("%d\n", (maxX-minX)*(maxY-minY));
	return 0;
}
