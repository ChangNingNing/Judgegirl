#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 16

int N, end;
int readnum[MAXN], readIndex[MAXN] = {0};
char fName[MAXN][MAXN];
FILE *fin[MAXN];

int main(){
	scanf("%d", &N);
	int bunch = (1<<17)/N;
	int readin[N][bunch];
	for(int i=0; i<N; i++){
		scanf("%s", fName[i]);
		fin[i] = fopen(fName[i], "rb");
		readnum[i] = fread(&readin[i], sizeof(int), bunch, fin[i]);
		if(readnum[i]==0) end++;
	}

	while(end != N){
		int min = INT_MAX, minP;
		for(int i=0; i<N; i++){
			if(readnum[i]==0) continue;
			if(readin[i][readIndex[i]] < min) min = readin[i][readIndex[i]], minP = i;
		}
		readIndex[minP]++;
		if(readIndex[minP] == readnum[minP]){
			readnum[minP] = fread(&readin[minP], sizeof(int), bunch, fin[minP]);
			readIndex[minP] = 0;
			if(readnum[minP]==0) end++;
		}
		printf("%d\n", min);
	}
	return 0;
}
