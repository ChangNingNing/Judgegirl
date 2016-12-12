#include <stdio.h>
#include <stdlib.h>

int main(){
	int a, b, c, d, e;
	scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

	int a2e = a - 2*e;
	int b2e = b - 2*e;
	int c2e = c - 2*e;
	int volume = a*b*c - a2e*c2e*d*2 - b2e*c2e*d*2 - b2e*a2e*d*2;
	int surface = (a*c + a*b + b*c) * 2 + a2e*d*8 + c2e*d*8 + b2e*d*8;

	printf("%d\n", surface);
	printf("%d\n", volume);
	return 0;
}
