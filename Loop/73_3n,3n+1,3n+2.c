#include <stdio.h>
#include <stdlib.h>

int main(){
	int x, i;
	int n = 0, n1 = 0, n2 = 0;
	scanf("%d", &x);
	for(i=0; i<x; i++){
		int tmp;
		scanf("%d", &tmp);
		if(tmp % 3 == 0) n++;
		else if(tmp % 3 == 1) n1++;
		else n2++; 
	}

	printf("%d %d %d\n", n, n1, n2);
}
