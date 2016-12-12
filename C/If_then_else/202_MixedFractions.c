#include <stdio.h>
#include <stdlib.h>

int GCD(int x, int y){
	while(y != 0){
		int temp = x;
		x = y;
		y = temp % y;
	}
	return x;
}

int main(){
	int a, b, c, d, e, f, g;
	scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g);
	b = (a>0)? a*c+b: a*c-b;
	f = (e>0)? e*g+f: e*g-f;
	a = e = 0;

	int h = 0, i, j;
	switch(d){
	case 0:// +
		j = c * g;
		i = b*g + c*f;
		break;
	case 1:// -
		j = c * g;
		i = b*g - c*f;
		break;
	case 2:// *
		j = c * g;
		i = b * f;
		break;
	case 3:// /
		j = c * f;
		i = b * g;
		break;
	}

	int gcd = GCD(i, j);
	gcd = (gcd > 0)? gcd: -1*gcd;
	i /= gcd;
	j /= gcd;
	if(j < 0){
		i *= -1;
		j *= -1;
	}
	int negativeFlag = 0;
	if(i < 0){
		i *= -1;
		negativeFlag = 1;
	}
	h = i/j;
	i %= j;
	if(negativeFlag == 1) h *= -1;
	if(i == 0) j = 1;

	printf("%d\n", h);
	printf("%d\n", i);
	printf("%d\n", j);

	return 0;
}
