#include <stdio.h>
#include <stdlib.h>

int A[14][14] = {0};
int r, c;

int Go(int x, int y){
	if(x==c && y==1) return 1;
	int answer = 0;
	if(x+1<=c && A[y][x+1]) answer += Go(x+1, y);
	if(y-1>=1 && A[y-1][x]) answer += Go(x, y-1);
	return answer;
}

int main(){
	scanf("%d %d", &r ,&c);
	for(int i=1; i<=r; i++){
		for(int j=1; j<=c; j++){
			scanf("%d", &A[i][j]);
		}
	}
	int answer = Go(1, r);
	printf("%d\n", answer);
	return 0;
}
