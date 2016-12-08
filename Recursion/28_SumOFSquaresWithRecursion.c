#include <stdio.h>

int SumOfSquares(int x){
	if(x==0) return 0;
	return SumOfSquares(x-1)+x*x;
}

int main(){
	int n;
	scanf("%d", &n);
	printf("%d\n", SumOfSquares(n));
	return 0;
}
