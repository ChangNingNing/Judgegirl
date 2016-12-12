#include "polynomial.h"
#include <stdio.h>
#define MAX(x, y) ((x)>(y)? (x): (y))

void init(Polynomial *poly, int coefficient[], int n){
	for(int i=0; i<n; i++) poly->coef[i] = coefficient[i];
	for(int i=n; i<4096; i++) poly->coef[i] = 0;
	poly->head = n-1;
	return;
}

Polynomial add(Polynomial *poly1, Polynomial *poly2){
	int coef[4096] = {0};
	int head = MAX(poly1->head, poly2->head);
	for(int i=0; i<=head; i++) coef[i] = poly1->coef[i] + poly2->coef[i];
	Polynomial ans;
	init(&ans, coef, head + 1);
	return ans;
}

Polynomial multiply(Polynomial *poly1, Polynomial *poly2){
	int coef[4096] = {0};
	for(int i=0; i<=poly1->head+1; i++){
		for(int j=0; j<=poly2->head+1; j++){
			coef[i+j] += poly1->coef[i] * poly2->coef[j];
		}
	}
	Polynomial ans;
	init(&ans, coef, poly1->head + poly2->head + 1);
	return ans;
}

void print(Polynomial *poly){
	for(int i=poly->head; i>=0; i--){
		if(poly->coef[i]==0) continue;
		printf("%+d", poly->coef[i]);
		if(i>1) printf("x^%d", i);
		else if(i == 1) putchar('x');
	}
	puts("");
}
