#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXL 1025

int main(){
	char file[128];
	scanf("%s", file);
	FILE *fin = fopen(file, "r");
	if(fin == NULL) return 1;

	fseek(fin, 0, SEEK_END);
	int fsize = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	char buffer[MAXL];
	int flines = 0, fwords = 0;
	while(fgets(buffer, MAXL, fin)){
		flines++;
		int length = strlen(buffer);
		for(int i=0; i<length; i++){
			if(isalpha(buffer[i])){
				while(isalpha(buffer[i])) i++;
				fwords++;
			}
		}
	}
	printf("%d %d %d\n", flines, fwords, fsize);
	return 0;
}
