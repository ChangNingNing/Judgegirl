#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char output[257][257];
int m;
int curN = 0, space = 0, spaceN = 0;
int outputN = 0;

void print(){
	space = m - curN;
	spaceN = 1;
	if(space!=0 && outputN>1 && space >= outputN - 1){
		spaceN += (space / (outputN-1));
		space %= (outputN-1);
	}
	for(int i=0; i<outputN; i++){
		printf("%s", output[i]);
		for(int j=0; j<spaceN && i<outputN-1; j++){
			printf(" ");
			curN++;
		}
		if(i < space){
			printf(" ");
			curN++;
		}
	}
	while(curN<m){
		printf(" ");
		curN++;
	}
	printf("\n");
}

int main(){
	char word[257];
	scanf("%d", &m);
	while(scanf("%s", word)!=EOF){
		int length = strlen(word);
		if(curN + length > m){
			curN--;
			print();
			outputN = 1;
			curN = length + 1;
			strncpy(output[0], word, 257);
		}
		else if(curN + length == m){
			strncpy(output[outputN++], word, 257);
			curN += length;
			print();
			outputN = curN = 0;
		}
		else{
			strncpy(output[outputN++], word, 257);
			curN += length + 1;
		}
	}
	if(outputN > 0){
		curN--;
		print();
	}
	return 0;
}
