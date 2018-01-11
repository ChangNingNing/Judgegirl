#include "construct.h"
#include <stdlib.h>

#define MAX(a, b) (a>b? a: b)
#define MIN(a, b) (a<b? a: b)


Node* ConstructTree(int S[],int N){
	if (N <= 0)
		return NULL;
	Node *root = (Node *)malloc(sizeof(Node));
	if (N == 1){
		root->small = -1;
		root->large = S[0];
		root->left = root->mid = root->right = NULL;
		return root;
	}

	root->small = MIN(S[0], S[1]);
	root->large = MAX(S[0], S[1]);
	int P[3][N], nP[3] = {0};
	for (int i=2; i<N; i++){
		if (S[i] < root->small)
			P[0][nP[0]++] = S[i];
		else if (S[i] > root->small && S[i] < root->large)
			P[1][nP[1]++] = S[i];
		else
			P[2][nP[2]++] = S[i];
	}
	root-> left = ConstructTree(P[0], nP[0]);
	root->  mid = ConstructTree(P[1], nP[1]);
	root->right = ConstructTree(P[2], nP[2]);
	return root;
}
