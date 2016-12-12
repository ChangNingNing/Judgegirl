#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char sentence[1000000];
	int nSentence = 0;
	while(fgets(sentence, 1000000, stdin)){
		int length = strlen(sentence);
		for(int i=0; i<length; i++){
			if(sentence[i]!='.') continue;
			else{
				if(i==length-2) nSentence++;
				else if(sentence[i+1]==' '&&sentence[i+2]==' ') nSentence++;
			}
		}
	}
	printf("%d\n", nSentence);
}
