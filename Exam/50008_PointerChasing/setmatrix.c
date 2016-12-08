#include <stdio.h>
#include "setmatrix.h"

void processSetMatrix(int ***ptr){
	for(int ***cur1 = ptr; *cur1!=NULL; cur1++){
		for(int **cur2 = *cur1; *cur2!=NULL; cur2++){
			for(int *itr = *cur2; *itr!=0; itr++){
				printf("%d ", *itr);
			}
		}
	}
	return;
}
