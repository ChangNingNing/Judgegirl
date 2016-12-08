#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *word[101][50000];
int nWord[101] = {0};
char *candidate[50000];

int isCan(char *s, char *t){
	int diff = 0, index = 0, length = strlen(s);
	for(int i=0; i<length && diff<2; i++, index++){
		if(s[index] != t[i]){
			diff++;
			index--;
		}
	}
	if(diff==1)
		if(s[length-1] != t[length]) diff++;
	if(diff < 2)
		return 1;
	return 0;
}

int compare(const void *a, const void *b){
	return strcmp(*(char **)a, *(char **)b);
}

int main(){
	int W, Q;
	scanf("%d", &W)==1;
	for(int i=0; i<W; i++){
		char *input = (char *)malloc(sizeof(char)*128);
		scanf("%s", input);
		int index = strlen(input);
		word[index][nWord[index]] = input;
		nWord[index]++;
	}

	scanf("%d", &Q)==1;
	for(int i=0; i<Q; i++){
		char tmp[128];
		scanf("%s", tmp);
		int length = strlen(tmp);
		int flag = 0, nCan = 0;
		// property 1
		for(int j=0; j<nWord[length]; j++){
			int diff = 0;
			for(int k=0; k<length && diff < 2; k++)
				if(word[length][j][k] != tmp[k]) diff++;
			if(diff == 0){
				flag = 1;
				break;
			}
			else if(diff == 1)
				candidate[nCan++] = word[length][j];
		}
		if(flag){
			printf(">%s\n", tmp);
			continue;
		}
		// property 2
		for(int j=0; j<nWord[length-1]; j++){
			if(isCan(word[length-1][j], tmp))
				candidate[nCan++] = word[length-1][j];
		}
		// property 3
		for(int j=0; j<nWord[length+1]; j++){
			if(isCan(tmp, word[length+1][j]))
				candidate[nCan++] = word[length+1][j];
		}
		
		if(nCan <= 0){
			printf("!%s\n", tmp);
			continue;
		}
		qsort(candidate, nCan, sizeof(candidate[0]), compare);
		printf("?");
		for(int i=0; i<nCan; i++) printf("%s%c", candidate[i], i==nCan-1? '\n': ' ');
	}
	return 0;
}
