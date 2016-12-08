#include <stdio.h>
#include <stdlib.h>

int A[102][102] = {0};

int main(){
	int n, i, j;
	scanf("%d", &n);
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			scanf("%d", &A[i][j]);
		}
	}
	int intersection = 0, T_junction = 0, turn = 0, dead_end = 0;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(A[i][j]){
				int tmp = 0;
				if(A[i-1][j]) tmp++;
				if(A[i+1][j]) tmp++;
				if(A[i][j-1]) tmp++;
				if(A[i][j+1]) tmp++;
				if(tmp==4) intersection++;
				else if(tmp==3) T_junction++;
				else if(tmp==2 && (!A[i-1][j] || !A[i+1][j]) && (!A[i][j-1] || !A[i][j+1])) turn++;
				else if(tmp==1) dead_end++;
			}
		}
	}
	printf("%d\n%d\n%d\n%d\n", intersection, T_junction, turn, dead_end);
	return 0;
}