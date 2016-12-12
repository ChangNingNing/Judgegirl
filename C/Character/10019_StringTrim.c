#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
	char input[101];
	while(fgets(input, 101, stdin)){
		int length = strlen(input);
		int head = 0, tail = length-1;
		for(int i=0; i<length; i++){
			if(isspace(input[i])) head++;
			else break;
		}
		for(int i=length-1; i>=0; i--){
			if(isspace(input[i])) tail--;
			else break;
		}
		for(int i=head; i<=tail; i++) printf("%c", input[i]);
		printf("\n");
	}
}
