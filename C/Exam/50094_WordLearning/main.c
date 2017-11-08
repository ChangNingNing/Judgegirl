#include <stdio.h>
#include <string.h>
#include <limits.h>

int L[26][26];
int isU[26];

int main(){
	int T;
	char train[128];
	scanf("%d", &T);
	while (scanf("%s", train)==1){
		int len = strlen(train);
		for (int i=1; i<len; i++)
			L[train[i-1]-'a'][train[i]-'a']++;
	}

	for (int i=0; i<26; i++)
		for (int j=0; j<26; j++)
			printf("%d%c", L[i][j], j!=25? ' ': '\n');

	int max = -1, maxR, maxC;
	for (int i=0; i<26; i++){
		for (int j=0; j<26; j++){
			if (L[i][j] > max){
				max = L[i][j];
				maxR = i, maxC = j;
			}
		}
	}
	isU[maxR] = isU[maxC] = 1;
	printf("%c%c", maxR+'a', maxC+'a');

	int cur = maxC;
	while (cur >= 0){
		int _max = -1, next;
		for (int i=0; i<26; i++){
			if (L[cur][i] > _max && isU[i]==0){
				_max = L[cur][i];
				next = i;
			}
		}
		if (_max > T){
			printf("%c", next+'a');
			isU[next] = 1;
			cur = next;
		}
		else {
			puts("");
			cur = -1;
		}
	}
	return 0;
}
