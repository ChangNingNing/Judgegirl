#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Expense {
	int Y, M, D, amount;
	char category[40];
} Expense;

Expense E[10001];
int nE = 0;

int compare(const void *a, const void *b){
	Expense tmp1 = *(Expense *)a;
	Expense tmp2 = *(Expense *)b;
	if(tmp1.Y != tmp2.Y) return tmp1.Y-tmp2.Y;
	if(tmp1.M != tmp2.M) return tmp1.M-tmp2.M;
	if(tmp1.D != tmp2.D) return tmp1.D-tmp2.D;
	return strncmp(tmp1.category, tmp2.category, 40);
}

int main(){
	while(scanf("%d %d %d %s %d", &(E[nE].Y), &(E[nE].M), &(E[nE].D), E[nE].category, &(E[nE].amount))!=EOF){
		nE++;
	}
	qsort((void *)E, nE, sizeof(E[0]), compare);

	for(int i=0; i<nE; i++){
		if(E[i].Y==E[i+1].Y && E[i].M==E[i+1].M && E[i].D==E[i+1].D && strncmp(E[i].category, E[i+1].category, 40)==0){
			E[i+1].amount += E[i].amount;
			E[i].Y = -1;
		}
	}
	for(int i=0; i<nE; i++){
		if(E[i].Y<0) continue;
		printf("%d %d %d %s %d\n", E[i].Y, E[i].M, E[i].D, E[i].category, E[i].amount);
	}
	return 0;
}
