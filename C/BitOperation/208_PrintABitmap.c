#include <stdio.h>
#include <stdlib.h>

int main(){
	int width, height;
	char one[2], zero[2];
	unsigned int A[1025];
	scanf("%d %d", &width, &height);
	scanf("%s %s", one, zero);
	int num = 0;
	while(scanf("%u", &A[num])!=EOF)
		num++;
	
	int index = 0;
	for(int i=0; i<num; i++){
		for(int j=31; j>=0; j--){
			if(index == width*height) break;
			if((A[i]>>j)&1) printf("%c", one[0]);
			else printf("%c", zero[0]);
			if(index % width == width-1) printf("\n");
			index++;
		}
	}
	return 0;
}
