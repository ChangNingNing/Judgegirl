#ifndef _COMPLEX_H
#define _COMPLEX_H
 
typedef struct complex {
	float real;
	float fake;
} complex;
 
void init(complex *c, float a, float b);
void complex_print(complex *x);
complex complex_add(complex *x, complex *y);
complex complex_sub(complex *x, complex *y);
complex complex_mul(complex *x, complex *y);
#endif
