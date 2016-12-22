#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000001
Node buff[MAXN];

Node* mk_list(int n) {
    Node *head, *cur;
    for (int i = 0; i < n; i++) {
        Node *u = &buff[i];
        u->v = sp_rand(), u->next = NULL;
        if(i != 0) cur->next = u;
		else head = u;
		cur = u;
    }
    return head;
}
void rm_list(Node *head){
	return;
}
