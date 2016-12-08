#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j, x;
	scanf("%d", &x);
	for(i=1; i<=x; i++){
		for(j=1; j<=i; j++){
			printf("%d", j);
		}
	}
	printf("\n");
}
