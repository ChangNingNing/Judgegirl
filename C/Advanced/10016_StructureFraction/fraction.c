#include "fraction.h"
#include <stdio.h>

Frac GCD(Frac x){
	Frac y;
	y.b = x.b;
	y.a = x.a;
	while(x.b!=0){
		long long tmp = x.b;
		x.b = x.a % x.b;
		x.a = tmp;
	}
	if(y.a==0){
		y.a = 0;
		y.b = 1;
	}
	else{
		y.b /= x.a;
		y.a /= x.a;
	}
	return y;
}

Frac normal(long long a, long long b){
	Frac x;
	x.a = a;
	x.b = b;
	x = GCD(x);
	return x;
}

Frac add(Frac x, Frac y) {
	Frac z;
	z.b = x.b * y.b;
	z.a = x.a*y.b + y.a*x.b;
	z = GCD(z);
	return z;
}

Frac subtract(Frac x, Frac y) {
	Frac z;
	z.b = x.b * y.b;
	z.a = x.a*y.b - y.a*x.b;
	z = GCD(z);
	return z;
}

Frac multipy(Frac x, Frac y) {
	Frac z;
	z.b = x.b * y.b;
	z.a = x.a * y.a;
	z = GCD(z);
	return z;
}

Frac divide(Frac x, Frac y) {
	Frac z;
	z.b = x.b * y.a;
	z.a = x.a * y.b;
	z = GCD(z);
	return z;
}
