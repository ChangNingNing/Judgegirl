#include <stdio.h>
#include "construct.h"

#define MAXN 65536

int T[MAXN];

void PrintTree( Node *root ){
	if (root == NULL){
		printf("N\n");
		return;
	}

	printf("%d\n", root->value);
	PrintTree(root->left);
	PrintTree(root->right);
	return;
}

int main(){
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; i++)
		scanf("%d", &T[i]);

	Node *tree = ConstructTree( T, N );

	PrintTree( tree );
	return 0;
}
