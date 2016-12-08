#include <stdio.h>
#include <stdlib.h>
#include "matrix_multiplication.h"
#define MAX 1000
static int A_elements[MAX], A_rowind[MAX], A_colind[MAX];
static int B_elements[MAX], B_rowind[MAX], B_colind[MAX];
int main(int argc, char const *argv[])
{    
    int N, M, S;
    scanf("%d %d %d", &N, &M, &S);
 
    int *ptrA[3]; 
    int *ptrB[3];
    ptrA[0] = A_elements, ptrA[1] = A_rowind, ptrA[2] = A_colind;
    ptrB[0] = B_elements, ptrB[1] = B_rowind, ptrB[2] = B_colind;
 
    for(int i = 0; i < N; ++i)
        scanf("%d", &A_elements[i]);
    for(int i = 0; i < N; ++i)
        scanf("%d", &A_rowind[i]);    
    for(int i = 0; i < N; ++i)
        scanf("%d", &A_colind[i]);            
    for(int i = 0; i < M; ++i)
        scanf("%d", &B_elements[i]);
    for(int i = 0; i < M; ++i)
        scanf("%d", &B_rowind[i]);    
    for(int i = 0; i < M; ++i)
        scanf("%d", &B_colind[i]);
 
    int *result = malloc(S*S*sizeof(int));
    matrix_multiplication(N, ptrA, M, ptrB, S, result);
    for (int i = 0; i < S; ++i)
    {
        for (int j = 0; j < S; ++j)
          {
              printf("%d ", result[i * S + j]);
          }   
          printf("\n");
    }
    return 0;
}
