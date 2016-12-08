#include <stdio.h>
#include <stdlib.h>

int main(){
	int a;
	while(scanf("%d", &a)!=EOF){
		int num = 0;
		int max = 0;
		for(int i=0; i<32; i++){
			if((a >> i) & 1){
				num++;
				if(num > max)
					max = num;
			}
			else num = 0;
		}
		printf("%d\n", max);
	}
	return 0;
}
