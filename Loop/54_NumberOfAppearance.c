#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	char N[3], M[8];
	int X = 0;
	scanf("%s %s", N, M);
	for(i=0; i<7; i++){
		if(M[i]==N[0] && M[i+1]==N[1]) X++;
	}
	printf("%d\n", X);
	return 0;
}
