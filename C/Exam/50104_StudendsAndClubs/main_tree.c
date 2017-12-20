#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 41

typedef struct Stud {
	char name[MAXC];
	struct Stud *left, *right;
} Stud;

typedef struct Club {
	char name[MAXC];
	struct Club *left, *right;
	Stud *root;
} Club;

Stud *insert_stud(Stud *root, char *name){
	if (root == NULL){
		root = (Stud *)malloc(sizeof(Stud));
		strcpy(root->name, name);
		root->left = root->right = NULL;
		return root;
	}

	int ret = strcmp(name, root->name);
	if (ret > 0)
		root->right = insert_stud(root->right, name);
	else if (ret < 0)
		root->left = insert_stud(root->left, name);
	return root;
}

Club *insert_club(Club *root, char *club, char *name){
	if (root == NULL){
		root = (Club *)malloc(sizeof(Club));
		strcpy(root->name, club);
		root->left = root->right = NULL;
		root->root = insert_stud(root->root, name);
		return root;
	}

	int ret = strcmp(club, root->name);
	if (ret == 0)
		root->root = insert_stud(root->root, name);
	else if (ret > 0)
		root->right = insert_club(root->right, club, name);
	else
		root->left = insert_club(root->left, club, name);
	return root;
}

int find_stud(Stud *root, char *name){
	if (root == NULL)
		return 0;
	int ret = strcmp(name, root->name);
	if (ret == 0)
		return 1;
	else if (ret > 0)
		return find_stud(root->right, name);
	else
		return find_stud(root->left, name);
}

Club *find_club(Club *root, char *club){
	if (root == NULL)
		return NULL;
	int ret = strcmp(club, root->name);
	if (ret == 0)
		return root;
	else if (ret > 0)
		return find_club(root->right, club);
	else
		return find_club(root->left, club);
}

int main(){
	int K;
	scanf("%d", &K);
	Club *root = NULL;
	for (int i=0; i<K; i++){
		int q;
		char name[MAXC], club[MAXC];
		scanf("%d %s %s", &q, name, club);
		root = insert_club(root, club, name);
	}

	int Q;
	scanf("%d", &Q);
	for (int i=0; i<Q; i++){
		int q;
		char name[MAXC], club[MAXC];
		scanf("%d", &q);
		if (q == 0){
			scanf("%s", club);
			Club *ret = find_club(root, club);
			if (ret != NULL)
				printf("%s\n", ret->root->name);
			else
				printf("None\n");
		}
		else {
			scanf("%s %s", name, club);
			Club *ret = find_club(root, club);
			if (ret == NULL)
				printf("-1\n");
			else
				printf("%d\n", find_stud(ret->root, name));
		}
	}
	return 0;
}
