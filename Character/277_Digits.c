#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int table[10][7] = {1, 1, 1, 0, 1, 1, 1,
		0, 0, 1, 0, 0, 1, 0,
		1, 0, 1, 1, 1, 0, 1,
		1, 0, 1, 1, 0, 1, 1,
		0, 1, 1, 1, 0, 1, 0,
		1, 1, 0, 1, 0, 1, 1,
		1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 0};

int main(){
	char input[11];
	int width, height;
	while(scanf("%s %d %d", input, &width, &height)!=EOF){
		int length = strlen(input);
		for(int i=0; i<height; i++){
			for(int j=0; j<length; j++){
				if(i==0 || i==height/2 || i==height-1){
					int index = 0;
					if(i>0) index = (i==height-1)? 6: 3;
					if(table[input[j]-48][index]){
						printf(" ");
						for(int k=0; k<width-3; k++)
							printf("%c", input[j]);
						printf("  ");
					}
					else{
						for(int k=0; k<width; k++)
							printf(" ");
					}
				}
				else{
					int index = (i<height/2)? 1: 4;
					if(table[input[j]-48][index]){
						printf("%c", input[j]);
						for(int k=0; k<width-3; k++)
							printf(" ");
					}
					else{
						for(int k=0; k<width-2; k++)
							printf(" ");
					}
					if(table[input[j]-48][index+1])
						printf("%c ", input[j]);
					else printf("  ");
				}
			}
			printf("\n");
		}
	}
}
