#include "array.h"
#include <stdio.h>
#include <stdlib.h>

#define NOSET -2147483647
#define OUTRANGE -2147483648

void init(ARRAY *a, int left, int right){
	a->l = left;
	a->r = right;
	for(int i=0; i<right-left+1; i++)
		a->array[i] = NOSET;
	return;
}

int set(ARRAY *a, int index, int value){
	if(index < a->l || index > a->r) return OUTRANGE;
	a->array[index - a->l] = value;
	return 1;
}

int get(ARRAY *a, int index){
	if(index < a->l || index > a->r) return OUTRANGE;
	return a->array[index - a->l];
}

void print(ARRAY *a){
	int range = a->r - a->l + 1;
	for(int i=0; i<range; i++){
		if(a->array[i] == NOSET) puts("No value");
		else printf("%d\n", a->array[i]);
	}
	return;
}

int compare(const void *a, const void *b){
	int A = *(int *)a, B = *(int *)b;
	if(A >B) return 1;
	if(A==B) return 0;
	return -1;
}
void sort(ARRAY *a){
	qsort(a->array, a->r - a->l + 1, sizeof(a->array[0]), compare);
	return;
}
