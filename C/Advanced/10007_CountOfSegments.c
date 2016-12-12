#include <stdio.h>
#include <stdlib.h>

int main(){
	int N;
	while(scanf("%d", &N)!=EOF){
		int segment = 1;
		int flag;
		scanf("%d", &flag);
		for(int i=1; i<N; i++){
			int temp;
			scanf("%d", &temp);
			if(flag!=temp){
				segment++;
				flag = temp;
			}
		}
		printf("%d\n", segment);
	}
	return 0;
}
