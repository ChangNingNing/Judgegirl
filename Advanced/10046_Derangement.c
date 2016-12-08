#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rule[10][10];
char output[11];
int isUsed[11];
int n, m;

void Derangement(int index){
	if(index >= n){
		output[n] = '\0';
		puts(output);
		return;
	}
	for(int i=0; i<n; i++){
		if(rule[i][index]) continue;
		if(isUsed[i]) continue;
		output[index] = i + 'A';
		isUsed[i] = 1;
		Derangement(index+1);
		isUsed[i] = 0;
	}
	return;
}

int main(){
	while(scanf("%d %d", &n, &m)!=EOF){
		memset(rule, 0, sizeof(rule));
		for(int i=0; i<m; i++){
			int x, y;
			scanf("%d %d", &x, &y);
			rule[x-1][y-1] = 1;
		}
		Derangement(0);
	}
	return 0;
}
