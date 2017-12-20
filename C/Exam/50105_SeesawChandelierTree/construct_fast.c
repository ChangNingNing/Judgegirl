#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "construct.h"

Node *myLink(int *T, int l, int r){
	if (l > r)
		return NULL;
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = T[r];
	root->left = myLink(T, l, r-1);
	root->right = NULL;
	return root;
}

Node *myConstruct(int *T, int64_t prefix[2][65536], int l, int r){
	if (r - l + 1 < 3)
		return myLink(T, l, r);

	int64_t sum = l==0? prefix[0][r]: prefix[0][r] - prefix[0][l-1];
	int64_t w = prefix[1][r] - prefix[1][l] - (sum - T[l]) * l;
	if (w % sum != 0)
		return myLink(T, l, r);
	int b = w / sum + l;

	Node *root = (Node *)malloc(sizeof(Node));
	root->value = T[b];
	root->left = myConstruct(T, prefix, l, b-1);
	root->right = myConstruct(T, prefix, b+1, r);
	return root;
}

int64_t prefix[2][65536];

Node *ConstructTree(int T[], int N){
	prefix[0][0] = prefix[1][0] = T[0];
	for (int i=1; i<N; i++){
		prefix[0][i] = prefix[0][i-1] + T[i];
		prefix[1][i] = prefix[1][i-1] + T[i] * i;
	}
	return myConstruct(T, prefix, 0, N-1);
}
