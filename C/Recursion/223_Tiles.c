#include <stdio.h>
#include <stdlib.h>

int Dir[4][3][2] = {1, 1, 1, 0, 0, 1,
		   -1, 1, 0, 1, -1, 0,
		   -1, -1, -1, 0, 0, -1,
		   1, -1, 0, -1, 1, 0};

void Split(int m, int n, int type, int x, int y){
	if(n==m) return;
	if(m==2 && n==1){
		printf("%d %d %d\n", type+1, x+Dir[type][0][0], y+Dir[type][0][1]);
		return;
	}
	
	Split(m/2, m/4, type, x, y);
	Split(m/2, m/4, type, x+Dir[type][0][0]*(m/4), y+Dir[type][0][1]*(m/4));
	Split(m/2, m/4, (type+1)%4, x+Dir[type][1][0]*m, y+Dir[type][1][1]*m);
	Split(m/2, m/4, (type+3)%4, x+Dir[type][2][0]*m, y+Dir[type][2][1]*m);

	Split(m/2, n, type, x+Dir[type][0][0]*(m/2), y+Dir[type][0][1]*(m/2));
}

int main(){
	int l, m;
	scanf("%d %d", &l, &m);
	Split(l, m, 0, 0, 0);
	return 0;
}
