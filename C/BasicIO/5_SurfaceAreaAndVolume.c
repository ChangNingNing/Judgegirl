#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j, k;
	scanf("%d %d %d", &i, &j, &k);

	printf("%d\n", 2*(i*j + j*k + i*k));
	printf("%d\n", i*j*k);
	return 0;
}
