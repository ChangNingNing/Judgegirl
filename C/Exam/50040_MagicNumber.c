#include <stdio.h>
#include <stdlib.h>

int main(){
	int M;
	scanf("%d", &M);
	if(M>0 && !(M&1) && (M>10000 || M<1000)) printf("1\n");
	else printf("0\n");
	return 0;
}
