#include "pair.h"
#include <stdio.h>
#include <stdlib.h>
 
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int *A = (int *) malloc(sizeof(int)*n);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        pairPrint(A, n);
        free(A);
    }
    return 0;
}
