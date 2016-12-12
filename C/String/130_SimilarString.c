#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(x, y) (x<y? 0: 1)

int main(){
	int n;
	scanf("%d", &n);
	while(n--){
		char input[2][81];
		int length[2];
		for(int i=0; i<2; i++){	
			scanf("%s", input[i]);
			length[i] = strlen(input[i]);
		}
		int similar = 0;
		if(length[0]==length[1]){
			for(int i=0; i<length[0]; i++){
				if(input[0][i]!=input[1][i]){
					if(i==length[0]-1) break;
					char temp = input[0][i];
					input[0][i] = input[0][i+1];
					input[0][i+1] = temp;
					if(strncmp(input[0], input[1], length[0])==0){
						similar = 1;
						break;
					}
					else break;
				}
			}
		}
		else if(length[0]-length[1]==1 || length[1]-length[0]==1){
			int minL = min(length[0], length[1]);
			for(int i=0; i<length[minL]; i++){
				if(input[0][i]!=input[1][i]){
					for(int j=i; j<length[minL]+1; j++)
						input[(minL+1)%2][j] = input[(minL+1)%2][j+1];
					if(strncmp(input[minL], input[(minL+1)%2], length[minL])==0){
						similar = 1;
						break;
					}
					else break;
				}
				if(i==length[minL]-1) similar = 1;
			}
		}
		if(similar) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
