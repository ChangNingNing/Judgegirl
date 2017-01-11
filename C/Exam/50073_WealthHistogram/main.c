#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAXN 1024

typedef struct {
	char n[12];
	int w;
} People;

People p[MAXN];

int compare(const void *a, const void *b){
	People *A = (People *)a, *B = (People *)b;
	if(A->w != B->w) return A->w - B->w;
	return strcmp(A->n, B->n);
}

int main(int argc, char *argv[]){
	FILE *fin = fopen(argv[1], "rb");
	assert(fin != NULL);
	int num = fread(p, sizeof(People), MAXN, fin);
	qsort(p, num, sizeof(p[0]), compare);
	int count = 1, index = p[0].w / 1000, max = p[0].w, maxP = 0;
	for(int i=1; i<num; i++){
		if(p[i].w / 1000 != index){
			printf("%d\n", count);
			count = 1, index = p[i].w / 1000;
		}
		else count++;
		if(p[i].w > max)
			max = p[i].w, maxP = i;
	}
	printf("%d\n", count);
	printf("%s\n", p[0].n);
	printf("%s\n", p[maxP].n);
	printf("%d\n", (num&1)? p[num/2].w: (int)(((long long int)p[num/2-1].w + p[num/2].w)/2));
	return 0;
}
