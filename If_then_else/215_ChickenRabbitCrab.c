#include <stdio.h>
#include <stdlib.h>

int main(){
	long long int chicken, rabbit, crab;
	long long int sum, foot, tail;
	int flag = 1;
	scanf("%lld %lld %lld", &sum, &foot, &tail);

	crab = sum - tail;
	if(crab < 0 ) flag = 0;
	else{
		if(foot%2 == 0){
			rabbit = foot/2 - 4*crab - tail;
			if(rabbit < 0) flag = 0;
			else{
				chicken = tail - rabbit;
				if(chicken < 0) flag = 0;
			}
		}
		else flag = 0;
	}

	if(flag)
		printf("%lld\n%lld\n%lld\n", chicken, rabbit, crab);
	else printf("0\n");
	return 0;
}
