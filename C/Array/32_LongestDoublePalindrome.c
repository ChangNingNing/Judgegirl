#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalin(char *A, int length){
	int i;
	int flag = 1;
	for(i=0; i<=length/2; i++){
		if(A[i]!=A[length-1-i]){
			flag = 0;
			break;
		}
	}
	return flag;
}

int main(){
	char input[251];
	char temp[251];
	fgets(temp, 250, stdin);
	int i=0, j=0, k=0;
	for(i=0; i<strlen(temp); i++){
		if(temp[i]==' ' || temp[i]=='\n') continue;
		input[j] = temp[i];
		j++;
	}
	input[j] = '\0';
	int answerP = 0;
	int answerL = 0;
	int flag = 0;
	for(i=strlen(input); i>0; i--){
		for(j=0; j<strlen(input) && j+i<=strlen(input); j++){
			for(k=1; k<i; k++){
				if(isPalin(input+j, k) &&  isPalin(input+j+k, i-k)){
					if(i >= answerL){
						answerP = j;
						answerL = i;
					}
					flag = 1;
					break;
				}
			}
		}
		if(flag) break;
	}
	for(i=0; i<answerL; i++){
		printf("%c", input[answerP+i]);
		if(i!=answerL-1) printf(" ");
	}
	return 0;
}