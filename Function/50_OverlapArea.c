#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
	return (a>b)? a: b;
}

int min(int a, int b){
	return (a>b)? b: a;
}

int area(int bx, int by, int tx, int ty){
	if(tx > bx && ty>by)
		return (tx-bx)*(ty-by);
	else
		return 0;
}

int main(){
	int bx[3], by[3], tx[3], ty[3];
	int A, B, C, AB, AC, BC, ABC;
	for(int i=0; i<3; i++)
		scanf("%d %d %d %d", &bx[i], &by[i], &tx[i], &ty[i]);
	A = area(bx[0], by[0], tx[0], ty[0]);
	B = area(bx[1], by[1], tx[1], ty[1]);
	C = area(bx[2], by[2], tx[2], ty[2]);
	AB = area(max(bx[0], bx[1]), max(by[0], by[1]), min(tx[0], tx[1]), min(ty[0], ty[1]));
	BC = area(max(bx[2], bx[1]), max(by[2], by[1]), min(tx[2], tx[1]), min(ty[2], ty[1]));
	AC = area(max(bx[0], bx[2]), max(by[0], by[2]), min(tx[0], tx[2]), min(ty[0], ty[2]));
	ABC = area(max(max(bx[0], bx[1]), bx[2]), max(max(by[0], by[1]), by[2]), min(min(tx[0], tx[1]), tx[2]), min(min(ty[0], ty[1]), ty[2]));

	printf("%d\n", A+B+C-AB-AC-BC+ABC);
	return 0;
}
