#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXP 20001
#define MAXC 16

typedef struct {
	char name[MAXC];
	int nC;
} Paper;
Paper P[MAXP];
int nP;

int main(){
	Paper _p;
	while (scanf("%s %d", _p.name, &_p.nC) != EOF)
		P[nP++] = _p;
	{
		int _comp(const void *a, const void *b){
			Paper *A = (Paper *)a, *B = (Paper *)b;
			int ret = strcmp(A->name, B->name);
			if (ret != 0) return ret;
			return B->nC - A->nC;
		}
		qsort(P, nP, sizeof(Paper), _comp);
	}

	for (int i=0, h=1; i<nP; i++, h++){
		if (P[i].nC < h){
			printf("%s %d\n", P[i].name, h-1);
			for (; i<nP; i++)
				if (i == nP-1 || strcmp(P[i].name, P[i+1].name)!=0) break;
			h = 0;
			continue;
		}
		if (i == nP-1 || strcmp(P[i].name, P[i+1].name)!=0){
			printf("%s %d\n", P[i].name, h);
			h = 0;
		}
	}
	return 0;
}
