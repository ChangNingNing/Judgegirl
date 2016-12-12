#include <stdio.h>
#include <stdlib.h>

#define pi 3.1415926

int main(){
	double a, b, c;
	scanf("%lf %lf %lf", &a, &b, &c);
	double area = 0.0;
	area += c*c*pi*3/4;
	if(c>b) area += (c-b)*(c-b)*pi/4;
	if(c>a) area += (c-a)*(c-a)*pi/4;
	printf("%f\n", area);
	return 0;
}
