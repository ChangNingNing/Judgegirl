#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T[26] = {0};
char input[3][11];

int try(int letter){
	if(letter>=26){
		char temp[3][11];
		for(int i=0; i<3; i++){
			int length = strlen(input[i]);
			for(int j=0; j<length; j++){
				if(input[i][j]>64){
					temp[i][j] = T[input[i][j]-'A'] + '0';
				}
				else temp[i][j] = input[i][j];
			}
			temp[i][length] = '\0';
		}
		int tmpInt[3];
		for(int i=0; i<3; i++) tmpInt[i] = atoi(temp[i]);
		if(tmpInt[0] * tmpInt[1] == tmpInt[2]) return 1;
		return 0;
	}
	if(T[letter]<0) return try(letter+1);
	int isAns = 0;
	for(int i=1; i<10; i++){
		T[letter] = i;
		isAns = try(letter+1);
		if(isAns) return 1;
	}
	return 0;
	
}

int main(){
	memset(T, -1, sizeof(T));
	for(int i=0; i<3; i++) scanf("%s", input[i]);
	for(int i=0; i<3; i++){
		int length = strlen(input[i]);
		for(int j=0; j<length; j++){
			if(input[i][j]>='A'){
				T[input[i][j]-'A'] = 0;
			}
		}
	}

	int isAns = try(0);

if(!isAns) printf("Wrong!!!\n");
	for(int i=0; i<3; i++){
		int length = strlen(input[i]);
		for(int j=0; j<length; j++){
			if(input[i][j]>='A') input[i][j] = T[input[i][j]-'A'] + '0';
		}
	}
	printf("%s x %s = %s\n", input[0], input[1], input[2]);
	return 0;
}
