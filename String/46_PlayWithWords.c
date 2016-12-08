#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define alpha (1<<9)
#define MAX (1<<15)
typedef struct Node {
	char value;
	int nLeft;
	int nRight;
	struct Node *left;
	struct Node *right;
} Node;

char ans[MAX];
int nAns = 0;

void myPrint(Node *root){
	if(root == NULL) return;
	myPrint(root->left);
	ans[nAns++] = root->value;
	assert(nAns < 100000);
	myPrint(root->right);
	free(root);
	return;
}

Node *BuildTree(char *input, int length){
	if(length==0) return NULL;
	Node *tmp = malloc(sizeof(Node));
	tmp->value = input[length/2];
	tmp->nLeft = length/2;
	tmp->nRight = length - length/2 - 1;
	tmp->left = BuildTree(input, length/2);
	tmp->right = BuildTree(input+length/2+1, length - length/2 - 1);
	return tmp;
}


Node *Compress(Node *root){
	nAns = 0;
	myPrint(root);
	return BuildTree(ans, nAns);
}

Node *Insert(Node *root, int index, char x){
	if(root==NULL){
		Node *tmp = malloc(sizeof(Node));
		tmp->nLeft = tmp->nRight = 0;
		tmp->left = tmp->right = NULL;
		tmp->value = x;
		return tmp;
	}
	
	if(abs(root->nLeft-root->nRight) >= alpha){
		root = Compress(root);
	}
	if(index > root->nLeft + 1){
		root->nRight++;
		root->right = Insert(root->right, index-root->nLeft-1, x);
		return root;
	}
	else{
		root->nLeft++;
		root->left = Insert(root->left, index, x);
		return root;
	}
	return NULL;
}

Node *Delete(Node *root, int index){
	if(root==NULL) return NULL;
	if(index > root->nLeft + 1){
		root->nRight--;
		root->right = Delete(root->right, index- root->nLeft - 1);
		return root;
	}
	if(index == root->nLeft + 1){
		if(root->nLeft > 0){
			Node *pre = NULL;
			Node *current = root->left;
			while(current->right!=NULL){
				current->nRight--;
				pre = current;
				current = current->right;
			}
			root->value = current->value;
			root->nLeft--;
			if(pre==NULL) root->left = current->left;
			else pre->right = current->left;
			return root;
		}
		if(root->nRight > 0){
			Node *pre = NULL;
			Node *current = root->right;
			while(current->left!=NULL){
				current->nLeft--;
				pre = current;
				current = current->left;
			}
			root->value = current->value;
			root->nRight--;
			if(pre==NULL) root->right = current->right;
			else pre->left = current->right;
			return root;
		}
		free(root);
		return NULL;
	}
	if(index <= root->nLeft){
		root->nLeft--;
		root->left = Delete(root->left, index);
		return root;
	}
	return NULL;
}

int main(){
	char ins[3][8];
	int num = 0;
	Node *root = NULL;
	int isHalt = 0;
	while(scanf("%s", ins[0])!=EOF){
		scanf("%s", ins[1]);
		switch(ins[0][0]){
		case 'i':
			scanf("%s", ins[2]);
			switch(ins[1][0]){
			case 'l':
				root = Insert(root, 1, ins[2][0]);
				break;
			case 'r':
				root = Insert(root, num+1, ins[2][0]);
				break;
			default:
				root = Insert(root, atoi(ins[1]), ins[2][0]);
				break;
			}
			num++;
			break;
		case 'd':
			switch(ins[1][0]){
			case 'l':
				root = Delete(root, 1);
				break;
			case 'r':
				root = Delete(root, num);
				break;
			default:
				root = Delete(root, atoi(ins[1]));
				break;
			}
			num--;
			break;
		default:
			printf("Halt\n");
			isHalt = 1;
			break;
		}
		if(isHalt) break;
	}
	nAns = 0;
	myPrint(root);
	char pre;
	int count = 1;
	int max = 0;
	char maxC[5001];
	int nMax = 0;
	for(int i=0; i<nAns; i++){
		if(ans[i]==pre){
			count++;
		}
		else{
			pre = ans[i];
			count = 1;
		}
		if(count > max){
			max = count;
			nMax = 0;
			maxC[nMax++] = ans[i];
		}
		else if(count == max){
			maxC[nMax++] = ans[i];
		}
	}
	for(int i=0; i<nMax; i++){
		printf("%c ", maxC[i]);
	}
	printf("%d\n", max);
	return 0;
}
