#include "construct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef MAXLENGTH
#define MAXLENGTH 0
#endif
#define MAXN 16384

Node node[MAXN];
int B[MAXN];

Node *myLink(int A[], int l, int r){
	if (r - l + 1 <= 0)
		return NULL;
	node[r].left = myLink(A, l, r-1);
	return &node[r];
}

Node *myConstruct(int A[], int l, int r){
	int N = r - l + 1;
	if (N < MAXLENGTH)
		return myLink(A, l, r);

	int pivot = A[MAXLENGTH - 1];
	int L[pivot - l + 1], R[r - pivot + 1];
	int nL = 0, nR = 0;
	for (int i=0; i<N; i++){
		if (A[i] < pivot)
			L[nL++] = A[i];
		else if (A[i] > pivot)
			R[nR++] = A[i];
	}
	node[pivot].left = myConstruct(L, l, pivot - 1);
	node[pivot].right = myConstruct(R, pivot + 1, r);
	return &node[pivot];
}

Node *ConstructTree(int S[], int N){
	for (int i=0; i<N; i++){
		node[i].value = S[i];
		node[i].left = node[i].right = NULL;
		B[i] = i;
	}

	{
		int comp(const void *a, const void *b){
			int A = *(int *)a, B = *(int *)b;
			return node[B].value - node[A].value;
		}
		qsort(B, N, sizeof(int), comp);
	}
	return myConstruct(B, 0, N-1);
}
