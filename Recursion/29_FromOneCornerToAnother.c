#include <stdio.h>
#include <stdlib.h>

int r, c;

int Go(int x, int y){
	if(x==c && y==r) return 1;
	int answer = 0;
	if(x+1 <= c) answer += Go(x+1, y, 1);
	if(y+1 <= r) answer += Go(x, y+1, 0);
	return answer;
}

int main(){
	scanf("%d %d", &r, &c);
	int answer = Go(1, 1);
	printf("%d\n", answer);
	return 0;
}
