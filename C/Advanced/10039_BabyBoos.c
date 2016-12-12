#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Letter{
	int n;
	int index[10000];
	char letter;
} Letter;

char input[100002];
char output[100002];

int main(){
	Letter table[26];
	for(int i=0; i<26; i++){
		table[i].letter = i+'A';
		table[i].n = 0;
	}
	
	scanf("%s", input);
	int length = strlen(input);
	for(int i=length-1; i>=0; i--){
		table[input[i]-'A'].index[table[input[i]-'A'].n] = i;
		table[input[i]-'A'].n++;
	}
	
	int N;
	scanf("%d", &N);
	while(N--){
		char u[2], v[2];
		scanf("%s %s\n", u, v);
		for(int i=0; i<26; i++){
			if(table[i].letter == v[0]) table[i].letter = u[0];
		}
	}
/*
for(int i=0; i<4; i++){
	printf("%c\n", table[i].letter);
	for(int j=0; j<table[i].n; j++){
		printf("%d ", table[i].index[j]);
	}
	printf("\n");
}
*/
	int nOutput = 0;
	for(int i=0; i<26; i++){
		for(int j=0; j<table[i].n; j++){
			output[table[i].index[j]] = table[i].letter;
			nOutput++;
		}
	}
	output[nOutput] = '\0';
	
	puts(output);
	return 0;
}
