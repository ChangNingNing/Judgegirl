#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char input[1001];
	while(scanf("%s", input)!=EOF){
		int length = strlen(input);
		int fPos = -1;
		int lPos = -1;
		for(int i=0; i<=length; i++){
			if(input[i]>='0' && input[i]<='9'){
				if(fPos < 0) fPos = lPos = i;
				else lPos = i;
			}
			else{
				if(fPos < 0) continue;
				char tmp[1001];
				strncpy(tmp, input+fPos, lPos-fPos+1);
				tmp[lPos-fPos+1] = '\0';
				printf("%d\n", atoi(tmp));
				fPos = lPos = -1;
			}
		}
	}
}
