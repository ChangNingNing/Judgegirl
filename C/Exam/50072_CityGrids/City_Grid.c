#include "City_Grid.h"
#include <stdio.h>
#include <string.h>

#define MAXN 10000

char visit[MAXN] = {0};

int DFS(City *root){
	if(root == NULL || visit[root->label]) return 0;
	visit[root->label] = 1;
	int flag = 0;
	if(root->east != NULL && root->north != NULL)
		if(root->east->north != NULL && root->north->east != NULL)
			flag = 1;
	return flag + DFS(root->east) + DFS(root->north);
}

int City_Grid(City *capital){
	memset(visit, 0, sizeof(visit));
	return DFS(capital);
}
