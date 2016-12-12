#include <stdio.h>
#include <stdlib.h>

int main(){
	int sum = 0;
	int temp;
	while(scanf("%d", &temp)!=EOF){
		sum+=temp;
	}
	printf("%d\n", sum);
	return 0;
}
