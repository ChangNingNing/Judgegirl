#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sol[17] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

void swap(char *T, int zeroP, int y){
	T[zeroP] = T[y];
	T[y] = 0;
	return;
}

int Move(char *T, int zeroP, int step){
// 0:up, 1:right, 2:left, 3:down
	int x = zeroP / 4, y = zeroP % 4;
	if(step == 0){
		if(x == 0) return -1;
		swap(T, zeroP, (x-1)*4+y);
		return (x-1)*4+y;
	}
	else if(step == 1){
		if(y == 3) return -1;
		swap(T, zeroP, x*4+(y+1));
		return x*4+(y+1);
	}
	else if(step == 2){
		if(y == 0) return -1;
		swap(T, zeroP, x*4+(y-1));
		return x*4+(y-1);
	}
	else if(step == 3){
		if(x == 3) return -1;
		swap(T, zeroP, (x+1)*4+y);
		return (x+1)*4+y;
	}
	return -1;
}

int Puzzle(char *T, int zeroP, int pre, int k){
	if(!strcmp(T, sol)) return 1;
	if(k <= 0) return 0;
	if((3 - zeroP/4) + (3 - zeroP%4) > k) return 0;
	int diff = 0;
	for(int i=0; i<16; i++) if(T[i]!=sol[i]) diff++;
	if(diff / 2 > k) return 0;

	int flag = 0;
	for(int i=0; i<4; i++){
		if(i == 3 - pre) continue;
		int P = Move(T, zeroP, i);
		if(P >= 0){
			flag = Puzzle(T, P, i, k-1);
			if(flag) break;
			Move(T, P, 3 - i); // MoveBack
		}
	}
	if(flag) return 1;
	return 0;
}

int main(){
	int K;
	while(scanf("%d", &K)==1){
		char T[17];
		int zeroP;
		for(int i=0; i<16; i++){
			int tmp;
			scanf("%d", &tmp);
			T[i] = tmp;
			if(tmp==0) zeroP = i;
		}
		printf("%d\n", Puzzle(T, zeroP, -1, K));
	}
	return 0;
}
