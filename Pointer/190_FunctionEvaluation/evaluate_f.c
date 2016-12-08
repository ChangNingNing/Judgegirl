#include "evaluate_f.h"
#include <limits.h>


/* f(x, y) = 4x-6y */
int evaluate_f(int *iptr[], int n, int *index){
	int max = INT_MIN;
	*index = -1;
	for(int i=0; i<n; i++){
		if(*iptr[i]*4 - *(iptr[i]+1)*6 > max){
			max = *iptr[i]*4 - *(iptr[i]+1)*6;
			*index = i;
		}
	}
	return max;
}
