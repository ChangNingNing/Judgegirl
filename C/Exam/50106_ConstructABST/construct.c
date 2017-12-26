#include "construct.h"
#include <stdlib.h>
#include <string.h>

Node *myInsert(Node *root, const char *n, const int h, const int w){
	if (root == NULL){
		root = (Node *)malloc(sizeof(Node));
		strcpy(root->name, n);
		root->height = h;
		root->weight = w;
		root->left = root->right = NULL;
		return root;
	}
	#ifdef HEIGHT
	if (h > root->height)
		root->right = myInsert(root->right, n, h, w);
	else
		root->left = myInsert(root->left, n, h, w);
	#endif
	#ifdef WEIGHT
	if (w > root->weight)
		root->right = myInsert(root->right, n, h, w);
	else
		root->left = myInsert(root->left, n, h, w);
	#endif
	return root;
}

Node *ConstructBSTree(int N, char name[][16], int height[], int weight[]){
	Node *root = NULL;
	for (int i=0; i<N; i++){
		root = myInsert(root, name[i], height[i], weight[i]);
	}
	return root;
}
