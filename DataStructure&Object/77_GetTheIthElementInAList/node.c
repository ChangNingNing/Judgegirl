#include "node.h"
#include <stdio.h>

struct node *getNode(struct node *head, unsigned int i){
	int num = 0;
	struct node *current = head;
	while(current->next!=NULL){
		current = current->next;
		num++;
	}
	if(i>num) return NULL;
	i = num - i;
	current = head;
	while(i){
		current = current->next;
		i--;
	}
	return current;
}
