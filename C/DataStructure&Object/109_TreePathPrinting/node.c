#include "node.h"
#include <stdio.h>

void myPrint(struct node *root, int path[], int pathN){
	if(root==NULL) return;
	path[pathN++] = root->data;

	if(root->left==NULL && root->right==NULL){
		for(int i=0; i<pathN; i++){
			if(i!=0) printf(" ");
			printf("%d", path[i]);
			if(i==pathN-1) printf("\n");
		}
		return;
	}
	myPrint(root->left, path, pathN);
	myPrint(root->right, path, pathN);
	return;
}

void print_all_paths(struct node *root){
	int path[1001] = {0};
	int pathN = 0;
	myPrint(root, path, pathN);
	return;
}
