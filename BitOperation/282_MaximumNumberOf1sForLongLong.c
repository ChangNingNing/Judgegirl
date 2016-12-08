#include <stdio.h>
#include <stdlib.h>

int main(){
	long long int a;
	while(scanf("%lld", &a)!=EOF){
		int count = 0;
		for(int i=0; i<64; i++)
			if((a>>i)&1) count++;
		printf("%d\n", count);
	}
	return 0;
}
