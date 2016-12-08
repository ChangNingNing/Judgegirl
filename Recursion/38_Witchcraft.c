#include <stdio.h>
#include <stdlib.h>

int lotion(int D, int a, int b, int c, int A, int B, int C, int turn){
	if(D==0) return 1;
	if(D<0) return 0;

	if(turn == 0){
		if(A>0 && D%A==0 && D/A<=a) return 1;
		int isLotion = 0;
		while(a>=0 && D>=0){
			isLotion += lotion(D, a, b, c, A, B, C, 1);
			a--;
			D -= A;
		}
		return isLotion;
	}
	else if(turn == 1){
		if(B>0 && D%B==0 && D/B<=b) return 1;
		int isLotion = 0;
		while(b>=0 && D>=0){
			isLotion += lotion(D, a, b, c, A, B, C, 2);
			b--;
			D -= B;
		}
		return isLotion;
	}
	else{
		if(C>0 && D%C==0 && D/C<=c) return 1;
		return 0;
	}
}

int main(){
	int A, B, C, D, a, b, c;
	int n;
	scanf("%d", &n);
	while(n--){
		scanf("%d %d %d %d %d %d %d", &D, &a, &b, &c, &A, &B, &C);
		if(lotion(D, a, b, c, A, B, C, 0)) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
