#include <stdio.h>
#include <stdlib.h>

int main(){
	char tmp[10];
	int num, sum = 0;
	while(scanf("%s %d", tmp, &num)!=EOF){
		sum += num;
	}
	printf("%d\n", sum);
	return 0;
}
