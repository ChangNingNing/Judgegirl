#include "pangfeng.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *myOrder;
int dim_n;

int compare(const void *a, const void *b){
	Row *x = (Row *)a;
	Row *y = (Row *)b;
	for(int i=0; i<dim_n; i++){
		if(x->score[myOrder[i]] != y->score[myOrder[i]])
			return y->score[myOrder[i]] - x->score[myOrder[i]];
	}
	return strncmp(x->name, y->name, 32);
}

void init(ExamTable *self, int n){
	self->nRow = 0;
	self->dim_n = n;
	return;
}

void addrow(ExamTable *self, char *name, int score[]){
	Row *curR = &(self->row[self->nRow]);
	strncpy(curR->name, name, 32);
	for(int i=0; i<self->dim_n; i++) curR->score[i] = score[i];
	self->nRow++;
	return;
}

void print(ExamTable *self, int order[]){
	printf("----- table begin -----\n");
	
	myOrder = order;
	dim_n = self->dim_n;
	qsort(self->row, self->nRow, sizeof(self->row[0]), compare);
	for(int i=0; i < self->nRow; i++){
		Row *tmp = &(self->row[i]);
		printf("%s", tmp->name);
		for(int j=0; j < self->dim_n; j++){
			printf(", %d", tmp->score[j]);
		}
		printf("\n");
	}

	printf("----- end         -----\n");
}
