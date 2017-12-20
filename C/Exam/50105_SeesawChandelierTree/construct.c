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

Node *myConstruct(int *T, int l, int r){
	if (r - l + 1 < 3)
		return myLink(T, l, r);

	int64_t sum = 0, w = 0, b;
	for (int i=l; i<=r; i++){
		sum += T[i];
		w += T[i] * (i - l);
	}
	assert(sum != 0);
	if (w % sum != 0)
		return myLink(T, l, r);
	b = w / sum + l;

	Node *root = (Node *)malloc(sizeof(Node));
	root->value = T[b];
	root->left = myConstruct(T, l, b-1);
	root->right = myConstruct(T, b+1, r);
	return root;
}

Node *ConstructTree(int T[], int N){ return myConstruct(T, 0, N-1); }
