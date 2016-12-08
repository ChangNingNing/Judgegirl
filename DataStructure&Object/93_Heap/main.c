#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(){
	struct Heap *heap = malloc(sizeof(struct Heap));
	initialize(heap);
	add(heap, 1);
	add(heap, 3);
	add(heap, 5);
	add(heap, 1);
	while(!isEmpty(heap)) printf("%d\n", removeMin(heap));
	return 0;
}
