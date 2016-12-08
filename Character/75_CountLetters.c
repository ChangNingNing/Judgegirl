#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int A[26] = {0};

int main(){
	char input[101];
	scanf("%s", input);
	int length = strlen(input);
	for(int i=0; i<length; i++){
		if(input[i]<97 && input[i]>90 || input[i]<65 || input[i]>122) continue;
		int index = (input[i]<97)? 65: 97;
		A[input[i]-index]++;
	}
	for(int i=0; i<26; i++) printf("%d\n", A[i]);
}
