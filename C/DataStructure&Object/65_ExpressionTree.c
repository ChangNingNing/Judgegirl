#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char MapK[50][33];
int MapV[50];
int nVar = 0;

int Compute(char *input){
	if(input[0] <= 57 && input[0]>47)
		return atoi(input);
	else if(input[0]=='('){
		int length = strlen(input);
		char operator = input[2];
		input[length-2] = '\0';
		input += 4;
		length -= 6;

		int split = 0;
		if(input[0]=='('){
			for(int i=0; i<length; i++){
				if(input[i]=='(') split--;
				if(input[i]==')') split++;
				if(input[i]==' ' && split==0){
					split = i;
					break;
				}
			}
		}
		else{
			for(int i=0; i<length; i++){
				if(input[i]==' '){
					split = i;
					break;
				}
			}
		}
		
		int right = Compute(input+split+1);
		input[split] = '\0';
		int left = Compute(input);
		switch(operator){
		case '+':
			return left + right;
		case '-':
			return left - right;
		case '*':
			return left * right;
		case '/':
			return left / right;
		}
	}
	else{
		int index;
		for(index=0; index<nVar; index++){
			if(strncmp(MapK[index], input, 33)==0) break;
		}
		return MapV[index];
	}
}

int main(){
	char line1[1001];
	fgets(line1, 1000, stdin);
	char line[1001];
	while(fgets(line, 1000, stdin)!=NULL){
		int length = strlen(line);
		int split = 0;
		for(int i=0; i<length; i++){
			if(line[i]=='='){
				split = i;
				break;
			}
		}
		MapV[nVar] = atoi(line+split+2);
		line[split-1] = '\0';
		strncpy(MapK[nVar], line, split-1);
		nVar++;
	}
	int length = strlen(line1);
	line1[length-1] = '\0';
	printf("%d\n", Compute(line1));
	return 0;
}
