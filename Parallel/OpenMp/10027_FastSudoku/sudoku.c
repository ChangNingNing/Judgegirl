#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAXN (1<<16)
#define SET(r, c, s, b) {pCur->isAllow[0][r]^=b; pCur->isAllow[1][c]^=b; pCur->isAllow[2][s]^=b;}
#define SET2(r, c, s, b) {isAllow[0][r]^=b; isAllow[1][c]^=b; isAllow[2][s]^=b;}

typedef struct {
	int isAllow[3][9], n;
} Node;

Node node[2][MAXN];
int empty[81][3], nEmpty = 0;

int DFS(int n, int isAllow[3][9]){
	if(n >= nEmpty) return 1;
	int row = empty[n][0], col = empty[n][1], square = empty[n][2];
	int tmpAllow = isAllow[0][row] & isAllow[1][col] & isAllow[2][square];
	int sum = 0;
	while(tmpAllow > 0){
		int p = tmpAllow & (-tmpAllow);
		tmpAllow ^= p;
		SET2(row, col, square, p);
		sum += DFS(n+1, isAllow);
		SET2(row, col, square, p);
	}
	return sum;
}

int BFS(){
	int sum=0, f=1, pre_l, pre_r, cur_l, cur_r=1;
	Node *bPre=node[1], *bCur=node[0], *pPre, *pCur;
	while(cur_r * 9 < MAXN && cur_r!=0){
		f=1-f, pre_l=0, pre_r=cur_r, cur_l=cur_r=0;
		{ Node *t = bPre; bPre = bCur; bCur = t; } // Swap
		pPre = bPre, pCur = bCur;
		while(pre_l < pre_r){
			if(pPre->n >= nEmpty){
				sum++, pre_l++, pPre++;
				continue;
			}
			int pos = pPre->n;
			int row = empty[pos][0], col = empty[pos][1], square = empty[pos][2];
			int tmpAllow = pPre->isAllow[0][row] & pPre->isAllow[1][col] & pPre->isAllow[2][square];
			while(tmpAllow > 0){
				int p = tmpAllow & (-tmpAllow);
				tmpAllow ^= p;
				memcpy(pCur->isAllow, pPre->isAllow, sizeof(pPre->isAllow));
				SET(row, col, square, p);
				pCur->n = pos+1;
				cur_r++, pCur++;
			}
			pre_l++, pPre++;
		}
	}
	pCur = bCur;
	#pragma omp parallel for schedule(guided) reduction(+ : sum)
	for(int i=0; i<cur_r; i++)
		sum += DFS(pCur[i].n, pCur[i].isAllow);
	return sum;
}

int main(){
	for(int i=0; i<3; i++)
		for(int j=0; j<9; j++)
			node[0][0].isAllow[i][j] = (1<<10)-2;
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			int tmp;
			scanf("%d", &tmp);
			if(tmp != 0){
				int s = i/3*3+j/3, bit = 1<<tmp;
				node[0][0].isAllow[0][i] ^= bit;
				node[0][0].isAllow[1][j] ^= bit;
				node[0][0].isAllow[2][s] ^= bit;
			}
			else{
				empty[nEmpty][0] = i;
				empty[nEmpty][1] = j;
				empty[nEmpty][2] = i/3*3+j/3;
				nEmpty++;
			}
		}
	}
	node[0][0].n = 0;

	printf("%d\n", BFS());
	return 0;
}
