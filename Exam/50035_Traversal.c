#include <stdio.h>
#include <stdlib.h>

int M[512][500] = {0};
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main(){
	int n, m, sX, sY;
	while(scanf("%d %d %d %d", &n, &m, &sX, &sY)!=EOF){
		for(int i=1; i<m; i++) M[0][i] = 0; // up
		M[0][m-1] = 1;
		for(int i=0; i<m; i+=2) for(int j=1; j<n; j++) M[j][i] = 3; // left
		for(int i=1; i<m; i+=2) for(int j=1; j<n; j++) M[j][i] = 1; // right
		for(int i=2; i<m; i+=2) M[1][i] = 2; // down
		for(int i=1; i<m; i+=2) M[n-1][i] = 2; // down


//for(int i=m-1; i>=0; i--, puts("")) for(int j=0; j<n; j++) printf("%d ", M[j][i]);

		int curX = sX + dir[M[sX][sY]][0], curY = sY + dir[M[sX][sY]][1];
		printf("%d %d\n", sX, sY);
		while(curX != sX || curY != sY){
			printf("%d %d\n", curX, curY);
			int tmpX = curX, tmpY = curY;
			curX = tmpX + dir[M[tmpX][tmpY]][0];
			curY = tmpY + dir[M[tmpX][tmpY]][1];
		}
		printf("%d %d\n", sX, sY);
	}
	return 0;
}
