#include "compute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute(paper P[], int N){
	int nCited[1024][2] = {0};
	for (int i=0; i<N; i++){
		nCited[i][0] = i;
		for (int j=0; j<P[i].numCitedPaper; j++)
			nCited[P[i].citedPaperIndex[j]][1]++;
	}

	int _comp1(const void *a, const void *b){
		int *A = (int *)a, *B = (int *)b;
		return strcmp(P[*A].journalName, P[*B].journalName);
	}
	int _comp2(const void *a, const void *b){
		paper *A = (paper *)a, *B = (paper *)b;
		return strcmp(A->journalName, B->journalName);
	}
	qsort(nCited, N, sizeof(nCited[0]), _comp1);
	qsort(P, N, sizeof(P[0]), _comp2);

	int nC = 0, nP = 0;
	for (int i=0; i<N; i++){
		nC += nCited[i][1];
		nP += 1;
		if (i==N-1 || strcmp(P[i].journalName, P[i+1].journalName)!=0){
			printf("%s %d/%d\n", P[i].journalName, nC, nP);
			nC = nP = 0;
		}
	}
	return;
}
