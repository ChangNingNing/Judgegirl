#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
 
Node *FlipTree(Node *root){
	if (root == NULL)
		return NULL;
	Node *new = (Node *)malloc(sizeof(Node));
	new->n = root->n;
	new->left = FlipTree(root->right);
	new->right = FlipTree(root->left);
	return new;
}

int isIdentical(Node *tree1, Node *tree2){
	return	tree1 == NULL?	(tree2 == NULL? 1: 0):
							(tree2 == NULL? 0:
											tree1->n == tree2->n &&
											isIdentical(tree1->left, tree2->left) &&
											isIdentical(tree1->right, tree2->right));
}

void depthAvg(Node *root){
	int sumD = 0;
	int nL = 0;
	void myTrace(Node *node, int level){
		if (node == NULL) return;
		if (node->left != NULL) myTrace(node->left, level+1);
		if (node->right != NULL) myTrace(node->right, level+1);
		if (node->left == NULL && node->right == NULL) sumD += level, nL += 1;
		return;
	}
	myTrace(root, 0);
	printf("%d/%d\n", sumD, nL);
	return;
}
