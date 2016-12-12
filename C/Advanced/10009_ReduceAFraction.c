#include <stdio.h>
#include <stdlib.h>

int GCD(int x, int y){
	while(x!=0){
		int a = x;
		x = y % x;
		y = a;
	}
	return y;
}

int main(){
	int x, y;
	while(scanf("%d %d", &x, &y)!=EOF){
		int gcd = GCD(x, y);
		printf("%d / %d\n", x/gcd, y/gcd);
	}
	return 0;
}
