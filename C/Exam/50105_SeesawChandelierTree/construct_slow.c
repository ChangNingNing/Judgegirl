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

	int b;
	for (b=l; b<=r; b++){
		int64_t wl = 0, wr = 0;
		for (int i=l; i<b; i++) wl += T[i] * (b - i);
		for (int i=b+1; i<=r; i++) wr += T[i] * (i - b);
		if (wl == wr) break;
	}
	if (b == r+1)
		return myLink(T, l, r);

	Node *root = (Node *)malloc(sizeof(Node));
	root->value = T[b];
	root->left = myConstruct(T, l, b-1);
	root->right = myConstruct(T, b+1, r);
	return root;
}

Node *ConstructTree(int T[], int N){ return myConstruct(T, 0, N-1); }
