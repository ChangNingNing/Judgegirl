#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MAXN 1024

typedef struct {
	int v, w, c;
	float uV;
} Object;

int W, N;
int bound = INT_MIN;
Object obj[MAXN];

int comByuV(const void *a, const void *b){
	Object *A = (Object *)a, *B = (Object *)b;
	if(A->uV > B->uV) return -1;
	else if(A->uV < B->uV) return 1;
	if(A->w > B->w) return -1;
	return 1;
}

float UGreedy(int index, int w){
	float ub = 0;
	for(int i=index; i<N && w < W; i++){
		float tmp = W - w;
		float k = tmp / obj[i].w;
		k = (k <= obj[i].c)? k: obj[i].c;
		w += k * obj[i].w;
		ub += (float)obj[i].v * k;
	}
	return ub;
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

void DFS(int index, int w, int v, float ub){
	if(w > W) return;
	if(ub <= bound) return;
	if(index >= N){
		if(v > bound) bound = v;
		return;
	}
	int tmp = W - w;
	int c = tmp / obj[index].w;
	c = (c <= obj[index].c)? c: obj[index].c;
	for(int i=c; i>=0; i--){
		float ub_tmp = v + obj[index].v*i + UGreedy(index + 1, w + obj[index].w * i);
		DFS(index + 1, w + obj[index].w*i, v + obj[index].v*i, ub_tmp);
	}
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
		obj[i].uV = (float)v/w;
	}
	qsort(obj, N, sizeof(obj[0]), comByuV);
	bound = LGreedy(0, 0);
	DFS(0, 0, 0, UGreedy(0, 0));
	printf("%d\n", bound);
	return 0;
}
