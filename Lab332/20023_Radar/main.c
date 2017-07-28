#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAXN 65536

int X, Y, D, N, T;
int D2;
int pos[MAXN][2];
int nEdge[MAXN];

static int Square(int x) { return x*x; }

void myRadar(){
	memset(nEdge, 0, sizeof(nEdge));
	for (int i=0; i<N; i++){
		for (int j=i+1; j<N; j++){
			int d2 = 0;
			d2 = Square(pos[i][0]-pos[j][0]) + Square(pos[i][1]-pos[j][1]);
			if (d2 <= D2) nEdge[i]++, nEdge[j]++;
		}
	}
	return;
}

uint32_t Hash(const int const * nPair, const int num){
	uint32_t ret = 0;
	for (int i=0; i<num; i++)
		ret += nPair[i] * (i+1);
	return ret;
}

int main(){
	scanf("%d %d %d", &X, &Y, &D);
	scanf("%d %d", &N, &T);

	D2 = Square(D);

	for (int t=0; t<T; t++){
		for (int i=0; i<N; i++){
			int tmpX, tmpY;
			scanf("%d %d", &tmpX, &tmpY);
			pos[i][0] += tmpX;
			pos[i][1] += tmpY;
		}
		myRadar();
		printf("%u\n", Hash(nEdge, N));
	}

	return 0;
}
