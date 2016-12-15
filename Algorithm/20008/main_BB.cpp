#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXN 1024

typedef struct {
	int v, w, c;
} Object;

int W, N;
int bound = INT_MIN;
Object obj[MAXN];

int compare(const void *a, const void *b){
	Object *A = (Object *)a, *B = (Object *)b;
	if((float)A->v/A->w > (float)B->v/B->w) return -1;
	return 1;
}

int UGreedy(int index, int w){
	float ub = 0;
	for(int i=index; i<N && w < W; i++){
		float tmp = W - w;
		float k = tmp / obj[i].w;
		k = (k <= obj[i].c)? k: obj[i].c;
		w += k * obj[i].w;
		ub += (float)obj[i].v * k;
	}
	return (int)ub;
}

int LGreedy(int index, int w){
	int lb = 0;
	for(int i=index; i<N && w < W; i++){
		int tmp = W - w;
		int k = tmp / obj[i].w;
		k = (k <= obj[i].c)? k: obj[i].c;
		w += k * obj[i].w;
		lb += k * obj[i].v;
	}
	return lb;
}

void DFS(int index, int w, int v){
	int ub = v + UGreedy(index, w);
	if(w > W) return;
	if(ub <= bound) return;
	if(index >= N){
		if(v > bound) bound = v;
		return;
	}
	int tmp = W - w;
	int c = tmp / obj[index].w;
	c = (c <= obj[index].c)? c: obj[index].c;
	for(int i=c; i>=0; i--)
		DFS(index + 1, w + obj[index].w*i, v + obj[index].v*i);
	return;
}

int main(){
	scanf("%d %d", &W, &N);
	for(int i=0; i<N; i++){
		int w, v, c;
		scanf("%d %d %d", &v, &w, &c);
		obj[i].v = v;
		obj[i].w = w;
		obj[i].c = c;
	}
	qsort(obj, N, sizeof(obj[0]), compare);
	bound = LGreedy(0, 0);
	DFS(0, 0, 0);
	printf("%d\n", bound);
	return 0;
}
