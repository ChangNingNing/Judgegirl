#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	scanf("%d", &i);

	printf("%d\n", i/100);
	i %= 100;
	printf("%d\n", i/10);
	i %= 10;
	printf("%d\n", i); 
	return 0;
}
