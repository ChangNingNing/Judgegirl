#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char input[1001];
	while(scanf("%s", input)!=EOF){
		if(input[0]=='-') break;
		int length = strlen(input);
		int even = 0, odd = 0;
		for(int i=0; i<length; i++){
			if(i&1) odd += input[i]-48;
			else even += input[i]-48;
		}

		if((input[length-1]-48)&1) printf("no");
		else printf("yes");

		if((even+odd) % 3 == 0) printf(" yes");
		else printf(" no");

		if((input[length-1]-48) % 5 == 0) printf(" yes");
		else printf(" no");

		if((even-odd) % 11 == 0) printf(" yes\n");
		else printf(" no\n");
	}
}
