#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, x;
	scanf("%d", &x);
	for(i=1; i<=x; i++)
		printf("%d\n", i);
	for(x--; x>0; x--)
		printf("%d\n", x);
}
