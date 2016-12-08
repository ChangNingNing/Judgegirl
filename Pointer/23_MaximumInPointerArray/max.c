#include <limits.h>
#include "max.h"

int max(int *iptr[], int n){
	int MAX = INT_MIN;
	for(int i=0; i<n; i++){
		if(*iptr[i] > MAX) MAX = *iptr[i];
	}
	return MAX;
}
