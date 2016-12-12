#include <stdio.h>
#include <string.h>
#include <assert.h>

char M[128][128];
char ans[128];
int n;

int IndependentSet(char *rule, int s, int rest, int m){
	if(m <= 0) return 1;
	if(n - s < m) return 0;
	if(s >= n) return 0;
	if(rest < m) return 0;

	int index;
	for(index=s; index<n && rule[index]>0; index++){}

	ans[index] = 1;
	int c = 0;
	for(int j=index+1; j<n; j++){
		if(M[index][j]==1) rule[j]++;
		if(rule[j] == 0) c++;
	}
	if(IndependentSet(rule, index+1, c, m-1)) return 1;
	
	c = 0;
	for(int j=index+1; j<n; j++){
		if(M[index][j]==1) rule[j]--;
		if(rule[j]==0) c++;
	}
	ans[index] = 0;
	if(IndependentSet(rule, index+1, c, m)) return 1;
	return 0;
}

int main(){
	int m;
	while(scanf("%d %d", &n, &m)==2){
		memset(ans, 0, sizeof(ans));
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				int tmp;
				scanf("%d", &tmp);
				M[i][j] = tmp;
			}
		}
		char rule[128] = {0};
		if(IndependentSet(rule, 0, n, m)){
			for(int i=0, c=0; i<n && c<m; i++){
				if(ans[i] == 1){
					printf("%d%c", i, c!=m-1? ' ': '\n');
					c++;
				}
			}
		}
		else printf("no solution\n");
	}
	return 0;
}
