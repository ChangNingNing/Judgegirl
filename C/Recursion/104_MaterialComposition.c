#include <stdio.h>
#include <stdlib.h>

int DEF[3][3];

int isUseUp(int A, int B, int C, int turn){
	if(A<0 || B<0 || C<0) return 0;
	if(A==0 && B==0 && C==0) return 1;
	if(turn>=2){
		if(A%DEF[2][0]==0 && B%DEF[2][1]==0 && C%DEF[2][2]==0
		&& A/DEF[2][0]==B/DEF[2][1] && A/DEF[2][0]==C/DEF[2][2])
			return 1;
		else return 0;
	}
	int tmpA = A - DEF[turn][0];
	int tmpB = B - DEF[turn][1];
	int tmpC = C - DEF[turn][2];
	int check = 0;
	check += isUseUp(tmpA, tmpB, tmpC, turn);
	check += isUseUp(A, B, C, turn+1);
	return check;
}

void Read(int n){
	if(n<=0) return;
	int A, B, C;
	scanf("%d %d %d", &A, &B, &C);
	if(isUseUp(A, B, C, 0)) printf("yes\n");
	else printf("no\n");
	Read(--n);
}

int main(){
	scanf("%d %d %d", &DEF[0][0], &DEF[0][1], &DEF[0][2]);
	scanf("%d %d %d", &DEF[1][0], &DEF[1][1], &DEF[1][2]);
	scanf("%d %d %d", &DEF[2][0], &DEF[2][1], &DEF[2][2]);
	int n;
	scanf("%d", &n);
	Read(n);
	return 0;
}
