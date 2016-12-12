#include <stdio.h>
#include <stdlib.h>
#include "pair.h"
#define MAXN 100000

typedef struct {
	int key, value;
} Map;

typedef struct {
	int sum, index[2];
} Pair;

int compare(const void *a, const void *b){
	Map *A = (Map *)a, *B = (Map *)b;
	if(A->value != B->value) return A->value - B->value;
	return A->key - B->key;
}

int compare2(const void *a, const void *b){
	Pair *A = (Pair *)a, *B = (Pair *)b;
	if(A->sum != B->sum) return A->sum - B->sum;
	return A->index[0] - B->index[0];
}

int compare3(const void *a, const void *b){
	Pair *A = (Pair *)a, *B = (Pair *)b;
	if(A->sum != B->sum) return -1*(A->sum - B->sum);
	return -1*(A->index[1] - B->index[1]);
}
void pairPrint(int numbers[], int n){
	Map map[MAXN];
	for(int i=0; i<n; i++)
		map[i].key = i, map[i].value = numbers[i];
	qsort(map, n, sizeof(map[0]), compare);
	
	Pair pair[MAXN/2];
	for(int i=0; i<n/2; i++){
		pair[i].sum = map[i].value + map[n-1-i].value;
		pair[i].index[0] = map[i].key;
		pair[i].index[1] = map[n-1-i].key;
		if(pair[i].index[0] > pair[i].index[1]){
			int tmp = pair[i].index[0];
			pair[i].index[0] = pair[i].index[1];
			pair[i].index[1] = tmp;
		}
	}
	
	#ifdef INC
	qsort(pair, n/2, sizeof(pair[0]), compare2);
	for(int i=0; i<n/2; i++)
		printf("%d = numbers[%d] + numbers[%d]\n", pair[i].sum, pair[i].index[0], pair[i].index[1]);
	#endif
	#ifdef DEC
	qsort(pair, n/2, sizeof(pair[0]), compare3);
	for(int i=0; i<n/2; i++)
		printf("%d = numbers[%d] + numbers[%d]\n", pair[i].sum, pair[i].index[1], pair[i].index[0]);
	#endif
	return ;
}
