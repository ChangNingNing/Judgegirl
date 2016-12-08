#include <stdio.h>
#include <stdlib.h>

int gf[10000] = {0};
int f[100] = {0};
int g[100] = {0};

int main(){
	int degF, degG;
	scanf("%d", &degF);
	for(int i=0; i<degF; i++)
		scanf("%d", &f[i]);
	scanf("%d", &degG);
	for(int i=0; i<degG; i++)
		scanf("%d", &g[i]);
	for(int i=0; i<degF; i++){
		for(int j=0; j<degG; j++){
			gf[i+j] += f[i] * g[j];
		}
	}
	for(int i=0; i<=degF+degG-2; i++){
		if(i!=0) printf(" ");
		printf("%d", gf[i]);
	}
	printf("\n");
	return 0;
}
