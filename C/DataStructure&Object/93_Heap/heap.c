#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b){
	if(*a == *b) return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
	return;
}

void initialize(struct Heap *heap){
	heap->num = 0;
	return;
}

int removeMin(struct Heap *heap){
	int remove = heap->ary[1];
	heap->ary[1] = heap->ary[heap->num];
	heap->num--;
	int index = 1, next = 2;
	while(next <= heap->num){
		if(next+1<=heap->num && heap->ary[next+1] < heap->ary[next]) 
			next++;
		if(heap->ary[index] > heap->ary[next]){
			swap(&(heap->ary[index]), &(heap->ary[next]));
			index = next, next = index * 2;
		}
		else break;
	}

	return remove;
}

void add(struct Heap *heap, int i){
	heap->ary[heap->num+1] = i;
	
	int index = heap->num+1;
	while(index/2>=1){
		if(heap->ary[index] < heap->ary[index/2]){
			swap(&(heap->ary[index]), &(heap->ary[index/2]));
			index /= 2;
		}
		else break;
	}
	heap->num++;
	return;
}

int isFull(struct Heap *heap){
	return heap->num==MAXHEAP-1;
}

int isEmpty(struct Heap *heap){
	return heap->num==0;
}
