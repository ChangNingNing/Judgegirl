#include "tree.h"
#include <stdlib.h>

Node *myBuild(int array[], int n, int index){
	if(index >= n) return NULL;
	Node *root = (Node *)malloc(sizeof(Node));
	root->label = array[index];
	root->left = myBuild(array, n, index*2+1);
	root->right = myBuild(array, n, index*2+2);
	return root;
}

Node *construct(int array[], int n){
	Node *root = myBuild(array, n, 0);
	return root;
}
