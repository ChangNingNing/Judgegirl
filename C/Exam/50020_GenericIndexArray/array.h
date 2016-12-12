#ifndef _ARRAY_H
#define _ARRAY_H

#define MAXN (1<<11)

typedef struct ARRAY {
	int l, r;
	int array[MAXN];
} ARRAY;
 
void init(ARRAY *a,  int left, int right);
int set(ARRAY *a, int index, int value);
int get(ARRAY *a, int index);
void print(ARRAY *a);
void sort(ARRAY *a);
 
#endif
