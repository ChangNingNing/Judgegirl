#include <stdio.h>
#include <stdlib.h>

int main(){
	int a;
	while(scanf("%d", &a)!=EOF){
		int num = 0;
		for(int i=0; i<32; i++){
			if((a >> i) & 1) num++;
		}
		printf("%d\n", num);
	}
	return 0;
}
