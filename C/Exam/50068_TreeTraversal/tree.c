#include "tree.h"
#include <stdio.h>

void invalid(int *flag, Node *cur){
	*flag = 0;
	printf("%d\n", cur->label);
}

void traversal(Node *root, int N, int command[]){
	int flag = 1, pos = 0;
	Node *history[N], *par;
	history[pos] = root;
	for(int i=0; i<N && flag; i++){
		switch(command[i]){
		case 0:
			invalid(&flag, history[pos]);
			break;
		case 1:
			printf("%d\n", history[pos]->label);
			break;
		case 2:
			if(pos - 1 < 0) invalid(&flag, history[pos]);
			else pos--;
			break;
		case 3:
			if(history[pos]->left == NULL) invalid(&flag, history[pos]);
			else history[pos+1] = history[pos]->left, pos++;
			break;
		case 4:
			if(history[pos]->right == NULL) invalid(&flag, history[pos]);
			else history[pos+1] = history[pos]->right, pos++;
			break;
		case 5:
			par = pos-1<0? NULL: history[pos-1];
			if(par == NULL) invalid(&flag, history[pos]);
			else{
				Node *sib = par->left == history[pos]? par->right: par->left;
				if(sib == NULL) invalid(&flag, history[pos]);
				else history[pos] = sib;
			}
			break;
		}
	}
	return;
}
