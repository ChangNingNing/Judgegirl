#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char output[128];
	char temp[128];
	scanf("%s", output);
	while(scanf("%s", temp)!=EOF){
		int length = strlen(output);
		for(int i=0; i<length; i++){
			if(output[i]==temp[0]){
				if(strncmp(output+i, temp, length-i)==0){
					int length2 = strlen(temp);
					strncat(output, temp+length-i, length2-length+i);
					break;
				}
			}
			if(i==length-1){
				int length2 = strlen(temp);
				strncat(output, temp, length2);
			}
		}
	}
	printf("%s", output);
}
