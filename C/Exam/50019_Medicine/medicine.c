#include "medicine.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void init(Medicine *medicine){
	medicine->nAct = medicine->nInact = medicine->weight = 0;
	return;
}

int addActive(Medicine *medicine , char *name, int weight){
	int index = -1;
	for(int i=0; i<medicine->nAct; i++)
		if(!strcmp(medicine->Act[i].name, name)) index = i;
	if(index < 0){
		if(medicine->nAct >= 2) return -1;
		strcpy(medicine->Act[medicine->nAct].name, name);
		medicine->Act[medicine->nAct].weight = weight;
		medicine->nAct++;
		medicine->weight += weight;
		return weight;
	}
	medicine->Act[index].weight += weight;
	medicine->weight += weight;
	return medicine->Act[index].weight;
}

int addInactive(Medicine *medicine, char *name, int weight){
	int index = -1;
	for(int i=0; i<medicine->nInact; i++){
		if(!strcmp(medicine->Inact[i].name, name)){
			index = i;
			break;
		}
	}
	if(index < 0){
		if(medicine->nInact >= 5) return -1;
		strcpy(medicine->Inact[medicine->nInact].name, name);
		medicine->Inact[medicine->nInact].weight = weight;
		medicine->nInact++;
		medicine->weight += weight;
		return weight;
	}
	medicine->Inact[index].weight += weight;
	medicine->weight += weight;
	return medicine->Inact[index].weight;
}

int compare(const void *a, const void *b){
	Ingredient *A = (Ingredient *)a, *B = (Ingredient *)b;
	if(A->weight != B->weight) return -1*(A->weight - B->weight);
	return strcmp(A->name, B->name);
}

void print(Medicine *medicine){
	qsort(medicine->Act, medicine->nAct, sizeof(medicine->Act[0]), compare);
	qsort(medicine->Inact, medicine->nInact, sizeof(medicine->Inact[0]), compare);
	puts("----- Active Ingredient begin   -----");
	for(int i=0; i<medicine->nAct; i++) printf("%d %s\n", medicine->Act[i].weight, medicine->Act[i].name);
	puts("----- end                       -----");
	puts("----- Inactive Ingredient begin -----");
	for(int i=0; i<medicine->nInact; i++) printf("%d %s\n", medicine->Inact[i].weight, medicine->Inact[i].name);
	puts("----- end                       -----");
	return;
}

int totalWeight(Medicine *medicine){ return medicine->weight; }

char *maxIngredient(Medicine *medicine){
	qsort(medicine->Act, medicine->nAct, sizeof(medicine->Act[0]), compare);
	qsort(medicine->Inact, medicine->nInact, sizeof(medicine->Inact[0]), compare);
	int max = -1;
	char *tmp = NULL;
	if(medicine->nAct > 0 && medicine->Act[0].weight > max){
		max = medicine->Act[0].weight;
		tmp = medicine->Act[0].name;
	}
	if(medicine->nInact > 0 && medicine->Inact[0].weight > max){
		max = medicine->Inact[0].weight;
		tmp = medicine->Inact[0].name;
	}
	else if(medicine->nInact > 0 && medicine->Inact[0].weight == max && strcmp(medicine->Inact[0].name, tmp) < 0)
		tmp = medicine->Inact[0].name;
	return tmp;
}
