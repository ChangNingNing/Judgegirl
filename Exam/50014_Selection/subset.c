#include "subset.h"
#include <stdio.h>
 
int subset(int numbers[], int n, int K, int S){
    if(S == 0){
    	if(K == 0) return 1;
	else return 0;
    }
    if(K <= 0) return 0;
    if(n < S) return 0;

    return subset(numbers+1, n-1, K-numbers[0], S-1) || subset(numbers+1, n-1, K, S);
}
