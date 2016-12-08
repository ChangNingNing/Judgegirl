#include <stdio.h>
#include <stdlib.h>
#include "activity.h"
#define MAXN 262144

int compare(const void *a, const void *b){
	Activity *A = (Activity *)a, *B = (Activity *)b;
	return A->end - B->end;
}

int select (Activity activities[], int n){
	qsort(activities, n, sizeof(activities[0]), compare);
	int isSelect[MAXN] = {0}, endTime = 0, count = 0;
	for(int i=0; i<n; i++){
		if(activities[i].start >= endTime){
			count++;
			endTime = activities[i].end;
			isSelect[i] = 1;
		}
	}
	#ifdef PRINT
	for(int i=0; i<n; i++)
		if(isSelect[i])
			printf("%d %d\n", activities[i].start, activities[i].end);
	#endif
	return count;
}
