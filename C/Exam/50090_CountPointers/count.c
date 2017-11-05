#include <stdio.h>
#include <stdlib.h>

#define MAXN 513
typedef struct {
	int *addr;
	int num;
} Obj;
Obj obj[MAXN];

int comp(const void *a, const void *b){
	Obj *A = (Obj *)a, *B = (Obj *)b;
	if (A->num != B->num) return A->num - B->num;
	return *(A->addr) - *(B->addr);
}

void count(int **p[]){
	int np = 0, nObj = 0;
	for (int **cur = p[np]; cur!=NULL; cur=p[++np]){
		int i;
		for (i=0; i<nObj; i++){
			if (obj[i].addr == *cur){
				obj[i].num++;
				break;
			}
		}
		if (i == nObj){
			obj[nObj].addr = *cur;
			obj[nObj].num = 1;
			nObj++;
		}
	}

	qsort(obj, nObj, sizeof(obj[0]), comp);

	for (int i=0; i<nObj; i++)
		printf("%d %d\n", *(obj[i].addr), obj[i].num);
}
