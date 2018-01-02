#include "construct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//#ifndef MAXLENGTH
//#define MAXLENGTH 0
//#endif

Node *myLink(int S[], int N){
	if (N <= 0)
		return NULL;
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = S[N-1];
	root->right = NULL;
	root->left = myLink(S, N-1);
	return root;
}

Node *ConstructTree(int S[], int N){
	if (N < MAXLENGTH)
		return myLink(S, N);

	int B[MAXLENGTH+1][2];
	memset(B, -1, sizeof(B));
	for (int i=0; i<N; i++){
		B[MAXLENGTH][0] = i;
		B[MAXLENGTH][1] = S[i];
		for (int j=MAXLENGTH; j>0; j--){
			if (B[j][1] > B[j-1][1]){
				int t0 = B[j-1][0], t1 = B[j-1][1];
				B[j-1][0] = B[j][0], B[j-1][1] = B[j][1];
				B[j][0] = t0, B[j][1] = t1;
			}
			else break;
		}
	}

	Node *root = (Node *)malloc(sizeof(Node));
	root->value = B[MAXLENGTH-1][1];
	root->left = ConstructTree(S, B[MAXLENGTH-1][0]);
	root->right = ConstructTree(S + B[MAXLENGTH-1][0] + 1, N - B[MAXLENGTH-1][0] - 1);
	return root;
}
