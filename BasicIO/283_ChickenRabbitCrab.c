#include <stdio.h>
#include <stdlib.h>

int main(){
	long long int chicken, rabbit, crab;
	long long int sum, foot, tail;
	scanf("%lld %lld %lld", &sum, &foot, &tail);

	crab = sum - tail;
	rabbit = foot/2 - 4*crab - tail;
	chicken = tail - rabbit;

	printf("%lld\n%lld\n%lld\n", chicken, rabbit, crab);
	return 0;
}
