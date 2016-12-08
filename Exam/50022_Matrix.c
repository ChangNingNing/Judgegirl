#include <stdio.h>
#include <stdlib.h>

int m, n;
int A[16][16] = {0};
int rowSum[17] = {0}, columnSum[17] = {0};
int T[17] = {0};

int matrix(int x, int y){
	if(y == 0)
		if(x-1 >= 0 && rowSum[x-1]!=0) return 0;
	if(x == m-1)
		if(y-1 >= 0 && columnSum[y-1]!=0) return 0;
	if(x==m){
		if(columnSum[n-1]!=0) return 0;
		return 1;
	}
	
	int C=m-x, min = 0, max = 0;
	for(int i=1; i<=n*m && C!=0; i++) if(T[i]==0) C--, min += i;
	C = m-x;
	for(int i=m*n; i>=1 && C!=0; i--) if(T[i]==0) C--, max += i;
	if(columnSum[y] < min || columnSum[y] > max) return 0;
	
	C = n-y, min = max = 0;
	for(int i=1; i<=n*m && C!=0; i++) if(T[i]==0) C--, min += i;
	C = n-y;
	for(int i=m*n; i>=1 && C!=0; i--) if(T[i]==0) C--, max += i;
	if(rowSum[x] < min || rowSum[x] > max) return 0;
	
	int flag = 0;
	for(int i=1; i<=m*n; i++){
		if(T[i]==1) continue;
		if(rowSum[x] - i<0 || columnSum[y] - i<0) break;
		A[x][y] = i;
		rowSum[x] -= i;
		columnSum[y] -= i;
		T[i] = 1;
		int nX = x, nY = y;
		if(y == n-1) nX++, nY = 0;
		else nX = x, nY++;
		flag = matrix(nX, nY);
		if(flag) break;
		
		rowSum[x] += i;
		columnSum[y] += i;
		T[i] = 0;
	}
	return flag;
}

int main(){
	while(scanf("%d %d", &m, &n)==2){
		for(int i=1; i<=m*n; i++) T[i] = 0;
		for(int i=0; i<m; i++) scanf("%d", &rowSum[i]);
		for(int i=0; i<n; i++) scanf("%d", &columnSum[i]);
		int flag = matrix(0, 0);
		if(!flag) printf("no solution\n");
		else
			for(int i=0; i<m; i++) for(int j=0; j<n; j++) printf("%d%c", A[i][j], j!=n-1? ' ': '\n');
	}
	return 0;
}
