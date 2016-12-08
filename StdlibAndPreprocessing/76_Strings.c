#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[65][50];
int inputN = 0;

int compare(const void *a, const void *b){
	return strncmp((char *)a, (char *)b, 50);
}

int main(){
	while(fgets(input[inputN], 50, stdin)!=NULL)
		inputN++;
	qsort((void *)input, inputN, sizeof(input[0]), compare);

	for(int i=0; i<inputN; i++) printf("%s", input[i]);
	return 0;
}
