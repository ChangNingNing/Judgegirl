#include <stdio.h>
#include <stdlib.h>

int a, b, c, d, e, p, q, r, s, x, y, F;

int changeDir(int i, int j){
	return (abs(a*i + b*j))%4;
}

int gold(int i, int j){
	return (abs(c*i + d*j))%e;
}

int main(){
	scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
	scanf("%d %d %d %d", &p, &q, &r, &s);
	scanf("%d %d %d", &x, &y, &F);
	
	int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int sum = 0;
	while(F>=0){
		if(x==p && y==q || x==r && y==s){
			if(x==p && y==q) x=r, y=s;
			else if(x==r && y==s) x=p, y=q;
		}
		else sum += gold(x, y);
		
		if(!F) break;
		F--;
		int newDir = changeDir(x, y);
		x += dir[newDir][0];
		y += dir[newDir][1];
	}
	printf("%d\n", sum);
	printf("%d %d\n", x, y);
	return 0;
}
