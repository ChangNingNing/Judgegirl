#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	scanf("%d", &i);
	if(i%3==0 && i%5==0 && i%7!=0)
		printf("0\n");
	else
		printf("1\n");
	return 0;
}
