#include <stdio.h>
#define MAXN 100
#define MAXM 5000

int **f[MAXN];
int *s[MAXN*101];

int ***constructTable(int A[], int B[]){
	int tA, tB, nA = 0, nB = 0, nS = 0, nF = 0;
	while (tA = A[nA]){
		for (int i=0; i<tA; i++){
			s[nS+i] = &B[nB];
			while (tB = B[nB]) nB++;
			nB++;
		}
		s[nS + tA] = NULL;
		f[nF] = &s[nS];
		nS += tA + 1;
		nA++, nF++;
	}
	f[nF] = NULL;
	return f;
}
