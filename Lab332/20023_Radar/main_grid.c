#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAXN 5000

int X, Y, D, N, T;
int D2;
int pos[MAXN][2];
int nEdge[MAXN];

typedef struct {
	int grid[2];
	int map;
} Node;
Node node[MAXN];

static int Square(int x) { return x*x; }

uint32_t Hash(const int const * nPair, const int num){
	uint32_t ret = 0;
	for (int i=0; i<num; i++)
		ret += nPair[i] * (i+1);
	return ret;
}

int myCompare(const void *A, const void *B){
	Node *a = (Node *)A, *b = (Node *)B;
	if (a->grid[0] != b->grid[0]) return a->grid[0] - b->grid[0];
	//return a->grid[1] - b->grid[1];
	if (a->grid[1] != b->grid[1]) return a->grid[1] - b->grid[1];
	return pos[a->map][1] - pos[b->map][1];
}

int myBS(int l, int r, int *grid){
	int key1 = grid[0] + 1;
	int key2 = grid[1] - 1;
	while (l <= r){
		int mid = (l + r) / 2;
		if (node[mid].grid[0] < key1) l = mid + 1;
		else if(node[mid].grid[0] > key1) r = mid - 1;
		else {
			if (node[mid].grid[1] < key2) l = mid + 1;
			else if(node[mid].grid[1] >= key2) r = mid - 1;
		}
	}

	if (l >= N ||
		node[l].grid[0] != key1 ||
		node[l].grid[1] > key2 + 2)
		return N;
	return l;
}

void myRadar(){
	memset(nEdge, 0, sizeof(nEdge));

	int curGrid[2] = {-1, -1}, curP = -1;

	for (int i=0; i<N; i++){
		int j;
		int m1 = node[i].map, m2;
		for (j=i+1; j<N; j++){
			if (node[i].grid[0] != node[j].grid[0] ||
				node[i].grid[1] <  node[j].grid[1] -1) break;
			m2 = node[j].map;
			//
			if (pos[m2][1] - pos[m1][1] > D) break;
			int d2 = Square(pos[m1][0]-pos[m2][0]) + Square(pos[m1][1]-pos[m2][1]);
			if (d2 <= D2) nEdge[m1]++, nEdge[m2]++;
		}

		if (node[i].grid[0] != curGrid[0] || node[i].grid[1] != curGrid[1]){
			curGrid[0] = node[i].grid[0];
			curGrid[1] = node[i].grid[1];

			curP = myBS(j, N-1, curGrid);
		}

		for (j= curP; j<N; j++){
			if (curGrid[0] != node[j].grid[0] - 1 ||
				curGrid[1] <  node[j].grid[1] - 1 ) break;
			m2 = node[j].map;
			//
			if (pos[m2][1] - pos[m1][1] > D) break;
			int d2 = Square(pos[m1][0]-pos[m2][0]) + Square(pos[m1][1]-pos[m2][1]);
			if (d2 <= D2) nEdge[m1]++, nEdge[m2]++;
		}
	}
	return;
}

int main(){
	scanf("%d %d %d", &X, &Y, &D);
	scanf("%d %d", &N, &T);

	D2 = Square(D);

	for (int i=0; i<N; i++)
		node[i].map = i;

	for (int t=0; t<T; t++){
		for (int i=0; i<N; i++){
			int tmpX, tmpY;
			scanf("%d %d", &tmpX, &tmpY);
			pos[i][0] += tmpX;
			pos[i][1] += tmpY;
		}
		for (int i=0; i<N; i++){
			node[i].grid[0] = pos[node[i].map][0] / D;
			node[i].grid[1] = pos[node[i].map][1] / D;
		}
		qsort(node, N, sizeof(node[0]), myCompare);
		myRadar();
		printf("%u\n", Hash(nEdge, N));
	}

	return 0;
}
