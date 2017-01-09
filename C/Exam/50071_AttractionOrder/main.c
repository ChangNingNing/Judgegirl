#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "attraction.h"

typedef struct {
	int x, y, circle, edge, index;
} MyAttraction;

Attraction tmp[MAXM];
MyAttraction attr[MAXM];

int Min(int x, int y){ return x < y? x: y; }

int compare(const void *a, const void *b){
	MyAttraction *A = (MyAttraction *)a, *B = (MyAttraction *)b;
	if(A->circle != B->circle) return A->circle - B->circle;
	if(A->edge != B->edge) return A->edge - B->edge;
	return A->index - B->index;
}

int main(int argc, char *argv[]){
	if(argc < 2) return 0;
	FILE *fin = fopen(argv[1], "rb");
	int N, M;
	assert(scanf("%d %d", &N, &M)==2);
	assert(fread(tmp, sizeof(Attraction), M, fin) == M);
	for(int i=0; i<M; i++){
		int x, y, circle, edge, index;
		x = tmp[i].x, y = tmp[i].y;
		circle = Min(Min(x, N-1-x), Min(y, N-1-y));
		if(y == circle)
			edge = 0, index = x - circle;
		else if(x == N - 1 - circle)
			edge = 1, index = y - circle;
		else if(y == N - 1 - circle)
			edge = 2, index = N - 1 - circle - x;
		else
			edge = 3, index = N - 1 - circle - y;
		attr[i].x = x, attr[i].y = y, attr[i].circle = circle;
		attr[i].edge = edge; attr[i].index = index;
	}
	qsort(attr, M, sizeof(attr[0]), compare);
	for(int i=0; i<M; i++) printf("%d %d\n", attr[i].x, attr[i].y);
	return 0;
}
