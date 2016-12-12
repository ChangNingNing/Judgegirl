#include "complex.h"
#include <stdio.h>
#include <stdlib.h>

void init(complex *c, float a, float b){
	c->real = a;
	c->fake = b;
	return;
}

void complex_print(complex *x){
	printf("%.3f%+.3fi\n", x->real, x->fake);
	return;
}

complex complex_add(complex *x, complex *y){
	x->real += y->real;
	x->fake += y->fake;
	return *x;
}

complex complex_sub(complex *x, complex *y){
	x->real -= y->real;
	x->fake -= y->fake;
	return *x;
}

complex complex_mul(complex *x, complex *y){
	complex tmp;
	tmp.real = x->real * y->real - x->fake * y->fake;
	tmp.fake = x->real * y->fake + x->fake * y->real;
	return tmp;
}
