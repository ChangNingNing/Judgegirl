#include <stdio.h>

int main(){
	int x=0, y=0, d, N, M;
	scanf("%d %d", &N, &M);
	printf("%d\n%d\n", x, y);
	while (scanf("%d", &d)!=EOF){
		int ins = d % 5;
		int tx = x, ty = y;
		if (ins==0) continue;
		else if (ins==1) tx += d;
		else if (ins==2) tx -= d;
		else if (ins==3) ty += d;
		else ty -= d;

		if (tx < 0 || tx >= N || ty < 0 || ty >= M) continue;

		x = tx, y = ty;
		printf("%d\n%d\n", x, y);
	}
	return 0;
}
