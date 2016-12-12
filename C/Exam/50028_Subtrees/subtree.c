#include "subtree.h"
#include <stdlib.h>

int n = 0;

int getCount(Node *root, int label[], int k){
	if(root == NULL) return 0;
	int leftN = getCount(root->left, label, k);
	int rightN = getCount(root->right, label, k);
	int self = (root->label==k)? 1: 0;
	if(!self && leftN && rightN) label[n++] = root->label;
	return leftN + rightN + self;
}

int getNode(Node *root, int label[], int k){
	n = 0;
	getCount(root, label, k);
	return n;
}
