#include <stdio.h>
#include <stdlib.h>

int GCD(int x, int y){
	while(x!=0){
		int temp = x;
		x = y%x;
		y = temp;
	}
	return y;
}

int main(){
	int og = 1, temp;
	while(scanf("%d", &temp)!=EOF){
		int gcd = GCD(temp, og);
		og = temp*og/gcd;
	}
	printf("%d\n", og);
	return 0;
}
