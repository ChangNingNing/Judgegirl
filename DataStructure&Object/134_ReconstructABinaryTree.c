#include <stdio.h>
#include <stdlib.h>
#define Min(x, y) ((x<y)? x: y)
#define Max(x, y) ((x>y)? x: y)

typedef struct Node {
	int value;
	int level;
	struct Node * left;
	struct Node * right;
} Node;

int input[1001][2];

void Insert(Node **root, int value, int level){
	Node *current = *root;
	Node *pre = NULL;
	while(current!=NULL){
		pre = current;
		current = (value>current->value)? current->right: current->left;
	}
	
	current = malloc(sizeof(Node));
	current->value = value;
	current->level = level;
	current->left = NULL;
	current->right = NULL;

	if(pre==NULL){
		*root = current;
		return;
	}
	if(value > pre->value) pre->right = current;
	else pre->left = current;
	return;
}

void myPrint(Node *root){
	if(root==NULL) return;
	printf("level = %d, value = %d\n", root->level, root->value);
	myPrint(root->left);
	myPrint(root->right);
	return;
}

int Search(Node *root, int value){
	Node *current = root;
	while(current != NULL){
		if(current->value==value) return current->level;
		else if(value > current->value) current = current->right;
		else current = current->left;
	}
	return -1;
}

int Dist(Node *root, int x, int y){
	Node *current = root;
	int diverse = 0;
	while(current != NULL){
		if(y < current->value) current = current->left;
		else if(x > current->value) current = current->right;
		else{
			diverse = current->level;
			int xLevel = Search(current, x);
			int yLevel = Search(current, y);
			return xLevel+yLevel-2*diverse;
		}
	}
	return -1;
}

int compare(const void *a, const void *b){
	int x = *((int *)a + 1);
	int y = *((int *)b + 1);
	return x - y;
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d %d", &input[i][0], &input[i][1]);
	}
	qsort(input, n, sizeof(input[0]), compare);
	
	Node *root = NULL;
	for(int i=0; i<n; i++) Insert(&root, input[i][0], input[i][1]);

//myPrint(root);

	int p;
	scanf("%d", &p);
	while(p--){
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%d\n", Dist(root, Min(x, y), Max(x, y)));
	}
	return 0;
}

