#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int value;
	struct Node *left;
	struct Node *right;
} node;

/* type 0=HLHR; 1=HRHL */
void myPrint(node *root, int type){
	if(root==NULL) return;
	printf("%d\n", (*root).value);
	if(type==0){
		myPrint((*root).left, (type+1)%2);
		printf("%d\n", (*root).value);
		myPrint((*root).right, (type+1)%2);
	}
	else{
		myPrint((*root).right, (type+1)%2);
		printf("%d\n", (*root).value);
		myPrint((*root).left, (type+1)%2);
	}
}

node *buildTree(char *input){
	if(input[0]!='('){
		int value = atoi(input);
		node *tmp = (node *)malloc(sizeof(node));
		(*tmp).value = value;
		(*tmp).left = NULL;
		(*tmp).right = NULL;
		return tmp;
	}
	int length = strlen(input);
	input[length-1] = '\0';
	input += 1;
	length -= 2;

	int mid = 0;
	for(int i=0; i<length; i++){
		if(input[i]=='(') mid++;
		else if(input[i]==')') mid--;
		else if(input[i]==',' && mid==0){
			mid = i;
			break;
		}
	}

	node *tmp = (node *)malloc(sizeof(node));
	(*tmp).right = buildTree(input+mid+1);
	input[mid] = '\0';
	(*tmp).left = buildTree(input);
	(*tmp).value = (*(*tmp).left).value + (*(*tmp).right).value;

	return tmp;
}

int main(){
	char input[4001];
	scanf("%s", input);
	node *head = buildTree(input);
	myPrint(head, 0);
	return 0;
}
