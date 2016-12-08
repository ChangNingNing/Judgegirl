#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int A[101][101] = {0};
int R[404] = {0};
int nR = 0;
int W, D;

int reflectDir[4] = {3, 2, 1, 0};
int step[2][4] = {-1, 0, 1, 0,
		  0, -1, 0, 1};

void Enter(int x, int y, int dir, int index){
	if(nR >= 2*(W+D)) return;
	if(R[index]>=0) return;
	while(1){
		x += step[0][dir];
		y += step[1][dir];
		if(!(x<D && x>=0 && y<W && y>=0)) break;
		if(A[x][y]==1) dir = reflectDir[dir];
	}
	int out = 0;
	if(x==D) out = y;
	else if(x==-1) out = 2*W+D-1-y;
	else if(y==W) out = (W+D)-1-x;
	else out = x+2*W+D;
	R[index] = out;
	R[out] = index;
	nR += 2;
	return;
}

int main(){
	scanf("%d %d", &W, &D);
	for(int i=0; i<D; i++){
		for(int j=0; j<W; j++){
			scanf("%d", &A[i][j]);
		}
	}

	memset(R, -1, (W+D)*2*sizeof(int));
	int index = 0;
	for(int i=0; i<W; i++) Enter(D, i, 0, index++);
	for(int i=D-1; i>=0; i--) Enter(i, W, 1, index++);
	for(int i=W-1; i>=0; i--) Enter(-1, i, 2, index++);
	for(int i=0; i<D; i++) Enter(i, -1, 3, index++);

	for(int i=0; i<nR; i++) printf("%d\n", R[i]);
	return 0;
}
