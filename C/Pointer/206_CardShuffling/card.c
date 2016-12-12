#include <stdio.h>
#include <math.h>
#include "card.h"

void shuffle(int *deck[]){
	int *first[5000];
	int *second[5000];
	int n = 0;
	while(deck[n]!=NULL)
		n++;
	for(int i=0; i<n; i++){
		if(i<(n+1)/2) first[i] = deck[i];
		else second[i-(n+1)/2] = deck[i];	
	}
	for(int i=0; i<n; i++){
		if(i&1) deck[i] = second[(i-1)/2];
		else deck[i] = first[i/2];
	}
}

void print(int *deck[]){
	int index = 0;
	while(deck[index]!=NULL){
		if(index>0) printf(" ");
		printf("%d", *deck[index]);
		index++;
	}
	if(index>0) printf("\n");
}
