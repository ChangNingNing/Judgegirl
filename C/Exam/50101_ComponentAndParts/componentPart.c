#include "componentPart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findPrice(int N,ComponentPart list[]){
	int _myPrice(int index){
		if (list[index].price > 0) return list[index].price;
		int ret = 0;
		for (int i=0; i<list[index].numComponent; i++)
			ret += _myPrice(list[index].componentPartList[i]);
		list[index].price = ret;
		return ret;
	}

	for (int i=0; i<N; i++)
		list[i].price = _myPrice(i);

	int _comp(const void *a, const void *b){
		ComponentPart *A = (ComponentPart *)a, *B = (ComponentPart *)b;
		return strcmp(A->name, B->name);
	}
	qsort(list, N, sizeof(list[0]), _comp);

	for (int i=0; i<N; i++)
		printf("%s %d\n", list[i].name, list[i].price);
	return;
}
