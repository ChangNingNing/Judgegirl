#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
	double a, b, c;
	while(scanf("%lf %lf %lf", &a, &b, &c)!=EOF){
		double r1;
		double r2;
		
		double discrim = b*b - 4.f*a*c;
		double rootDiscrim = sqrt(discrim);
		double q;
		if(b < 0) q = -.5f * (b - rootDiscrim);
		else q = -.5f * (b + rootDiscrim);
		r1 = q / a;
		r2 = c / q;
		if(r1 > r2){
			double t = r1;
			r1 = r2;
			r2 = t;
		}
		printf("%.20lf %.20lf\n", r1, r2);
	}
}
