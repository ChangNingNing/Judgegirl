#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) (x>y? x: y)

int main(){
	int num = 0;
	char temp[128];
	char abbr[128];
	while(scanf("%s", temp)!=EOF){
		int length = strlen(temp);
		if(temp[length-1]!='.'){
			if(strncmp(temp, "of", max(length, 2)) && strncmp(temp, "and", max(length, 3)) &&
			strncmp(temp, "the", max(length, 3)) && strncmp(temp, "at", max(length, 2)))
				abbr[num++] = (char)(temp[0]-32);
		}
		else{
			if(strncmp(temp, "of.", max(length, 3)) && strncmp(temp, "and.", max(length, 4)) &&
			strncmp(temp, "the.", max(length, 4)) && strncmp(temp, "at.", max(length, 3)))
				abbr[num++] = (char)(temp[0]-32);
			abbr[num] = '\0';
			printf("%s\n", abbr);
			num = 0;
			abbr[0] = '\0';
		}
	}

}
