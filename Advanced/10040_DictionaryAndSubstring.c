#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char D[200][52];
int nD = 0;

int main(){
	int N, Q;
	scanf("%d", &N);
	while(N--){
		scanf("%s", D[nD]);
		nD++;
	}

	scanf("%d", &Q);
	while(Q--){
		char query[52];
		scanf("%s", query);
		int n = 0;
		for(int i=0; i<nD; i++){
			if(strstr(D[i], query)>0) n++;
		}
		printf("%d\n", n);
	}

	return 0;
}
