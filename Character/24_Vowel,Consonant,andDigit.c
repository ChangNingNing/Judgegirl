#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
	char input[101];
	scanf("%s", input);
	int digits=0, letters=0, vowels=0, consonants=0;
	int length = strlen(input);
	for(int i=0; i<length; i++){
		if(isdigit(input[i])) digits++;
		else if(isalpha(input[i])){
			letters++;
			if(input[i]=='a'||input[i]=='e'||input[i]=='i'||input[i]=='o'||input[i]=='u'||input[i]=='A'||input[i]=='E'||input[i]=='I'||input[i]=='O'||input[i]=='U' ) vowels++;
			else consonants++;
		}
		else continue;
	}
	printf("%d %d %d %d\n", digits, letters, vowels, consonants);
	return 0;
}
