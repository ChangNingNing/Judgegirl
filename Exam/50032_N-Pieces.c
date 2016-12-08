#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 17
#define bound 300

int n, m, k;
char chess[MAXN][MAXN] = {0};
int check[MAXN*6] = {0};

int myCheck(int x, int y){
	if(check[x]<k && check[y+MAXN]<k && check[x+y+MAXN*2]<k && check[y-x+(n-1)+MAXN*4] < k) return 1;
	return 0;
}

int Put(int type, int x, int y, int putable){
	chess[x][y] = type==1? 'o': '.';
	check[x] += type;
	check[y + MAXN] += type;
	check[x + y + MAXN*2] += type;
	check[y - x + (n-1) + MAXN*4] += type;
	if(type != 1) return -1;
	if(check[x]==k){
		check[x]--;
		for(int i=y+1; i<n; i++) if(myCheck(x, i)) putable--;
		check[x]++;
	}
	if(check[y+MAXN]==k){
		check[y+MAXN]--;
		for(int i=x+1; i<n; i++) if(myCheck(i, y)) putable--;
		check[y+MAXN]++;
	}
	if(check[x+y+MAXN*2]==k){
		check[x+y+MAXN*2]--;
		for(int i=x+1, j=y-1; i<n && j>=0; i++, j--) if(myCheck(i, j)) putable--;
		check[x+y+MAXN*2]++;
	}
	if(check[y-x+(n-1)+MAXN*4]==k){
		check[y-x+(n-1)+MAXN*4]--;
		for(int i=x+1, j=y+1; i<n && j<n; i++, j++) if(myCheck(i, j)) putable--;
		check[y-x+(n-1)+MAXN*4]++;
	}
	return putable - 1;
}

int PlayChess(int x, int y, int rest, int putable){
	if(rest <= 0) return 1;
	if(x >= n) return 0;
	if(putable < rest) return 0;
	//if(((n-1)-x)*n + (n-y) < rest) return 0;
	
	int nY = (y+1) % n;
	int nX = (nY == 0)? x+1: x;
	if(myCheck(x, y)){
		int tmp = Put(1, x, y, putable);
		if(PlayChess(nX, nY, rest-1, tmp)) return 1;
		Put(-1, x, y, putable);
		return PlayChess(nX, nY, rest, putable-1);
	}
	else return PlayChess(nX, nY, rest, putable);
}

int main(){
	while(scanf("%d %d %d", &n, &m, &k)==3){
		memset(chess, '.', sizeof(chess));
		memset(check, 0, sizeof(check));
		if(PlayChess(0, 0, m, n*n)){
			for(int i=0; i<n; i++) chess[i][n] = '\0';
			for(int i=0; i<n; i++) puts(chess[i]);
		}
		else puts("N");
	}
	return 0;
}
