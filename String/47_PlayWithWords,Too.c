#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define alpha (1<<20)
#define MAX (1<<27)

typedef struct Node {
	char value;
	int n;
	int nLeft;
	int nRight;
	int RnLeft;
	int RnRight;
	struct Node *left;
	struct Node *right;
} Node;

int count(Node *root){
	if(root==NULL) return 0;
	return 1 + count(root->left) + count(root->right);
}

char PTc[MAX];
int PTi[MAX];
int nPT = 0;
void MyPrint(Node *root, int isFree){
	if(root == NULL) return;
	MyPrint(root->left, isFree);
	if(root->value == PTc[nPT]){
		PTi[nPT] += root->n;
	}
	else{
		nPT++;
		PTc[nPT] = root->value;
		PTi[nPT] = root->n;
	}
	MyPrint(root->right, isFree);
	if(isFree) free(root);
	return;
}

Node *BuildTree(int l, int r){
	if(l > r) return NULL;
	int mid = (l+r)/2;
	Node *tmp = malloc(sizeof(Node));
	tmp->value = PTc[mid];
	tmp->n = PTi[mid];
	tmp->RnLeft = mid - l;
	tmp->RnRight = r - mid;

	tmp->left = BuildTree(l, mid-1);
	tmp->right = BuildTree(mid+1, r);

	if(tmp->left) tmp->nLeft = tmp->left->nLeft + tmp->left->nRight + tmp->left->n;
	else tmp->nLeft = 0;
	if(tmp->right) tmp->nRight = tmp->right->nLeft + tmp->right->nRight + tmp->right->n;
	else tmp->nRight = 0;
	return tmp;
}

Node *Compress(Node *root){
	nPT = 0;
	MyPrint(root, 1);
	return BuildTree(1, nPT);
}

Node *Insert(Node *root, int index, char x, int num){
	if(root==NULL){
		Node *tmp = malloc(sizeof(Node));
		tmp->value = x;
		tmp->n = num;
		tmp->nLeft = tmp->nRight = 0;
		tmp->RnLeft = tmp->RnRight = 0;
		tmp->left = tmp->right = NULL;
		return tmp;
	}
	if(abs(root->RnLeft - root->RnRight) >= alpha){
		root = Compress(root);
	}
	if(index > root->nLeft + root->n){
		root->nRight += num;
		root->right = Insert(root->right, index-root->nLeft-root->n, x, num);
		root->RnRight = root->right->RnLeft + root->right->RnRight + 1;
		return root;
	}
	if(index <= root->nLeft + root->n && index > root->nLeft + 1){
		index = index - root->nLeft;
		Node *rRoot = malloc(sizeof(Node));
		rRoot->value = root->value;
		rRoot->n = root->n - (index-1);
		rRoot->RnLeft = 0;
		rRoot->RnRight = root->RnRight;
		rRoot->nLeft = 0;
		rRoot->nRight = root->nRight;
		rRoot->left = NULL;
		rRoot->right = root->right;

		root->n = index-1;
		root->RnRight = 0;
		root->nRight = 0;
		root->right = NULL;
		
		Node *tmp = malloc(sizeof(Node));
		tmp->value = x;
		tmp->n = num;
		tmp->RnLeft = root->RnLeft + 1;
		tmp->RnRight = rRoot->RnRight + 1;
		tmp->nLeft = root->n + root->nLeft;
		tmp->nRight = rRoot->n + rRoot->nRight;
		tmp->left = root;
		tmp->right = rRoot;
		return tmp;
	}
	if(index <= root->nLeft + 1){
		root->nLeft += num;
		root->left = Insert(root->left, index, x, num);
		root->RnLeft = root->left->RnLeft + root->left->RnRight + 1;
		return root;
	}
	return NULL;
}


int main(){
	char ins[4][10];
	int num = 0;
	Node *root = NULL;
	int isHalt = 0;
	while(scanf("%s", ins[0])!=EOF){
		switch(ins[0][0]){
		case 'i':
			scanf("%s %s %s", ins[1], ins[2], ins[3]);
			switch(ins[1][0]){
			case 'l':
				root = Insert(root, 1, ins[2][0], atoi(ins[3]));
				break;
			case 'r':
				root = Insert(root, num+1, ins[2][0], atoi(ins[3]));
				break;
			default:
				root = Insert(root, atoi(ins[1]), ins[2][0], atoi(ins[3]));
				break;
			}
			num += atoi(ins[3]);
			break;
		case 'p':
			nPT = 0;
			PTc[nPT] = -1;
			PTi[nPT] = 0;
			MyPrint(root, 0);
			for(int i=1; i<=nPT; i++)
				printf("%c %d ", PTc[i], PTi[i]);
			printf("$\n");
			break;
		default:
			printf("Halt\n");
			isHalt = 1;
			break;
		}
		if(isHalt) break;
	}
	return 0;
}
