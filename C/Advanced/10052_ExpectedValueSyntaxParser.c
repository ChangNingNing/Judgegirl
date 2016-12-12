#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float E(char *input){
	if(input[0]!='(') return atof(input);
	int length = strlen(input);
	input[length-1] = '\0';
	input += 1;
	length -= 2;
	
	char *tmp;
	int n = 0;
	for(tmp=input; tmp[0]!='\0'; tmp++){
		if(tmp[0]==' ' && n==0) break;
		else if(tmp[0]=='(') n++;
		else if(tmp[0]==')') n--;
	}
	input[tmp-input] = '\0';
	tmp += 1;
	float p = atof(input);

	char *tmp2;
	n = 0;
	for(tmp2=tmp; tmp2[0]!='\0'; tmp2++){
		if(tmp2[0]==' ' && n==0) break;
		else if(tmp2[0]=='(') n++;
		else if(tmp2[0]==')') n--;
	}
	tmp[tmp2-tmp] = '\0';
	tmp2 += 1;

	float expr1 = E(tmp), expr2 = E(tmp2);
	return p * (expr1+expr2) + (1 - p)*(expr1-expr2);
}

int main(){
	char input[2048];
	while(fgets(input, sizeof(input), stdin)!=0){
		int length = strlen(input);
		if(input[length-1]=='\n') input[length-1] = '\0';
		printf("%.2f\n", E(input));
	}
	return 0;
}
