#include <stdio.h>
#include <stdlib.h>

int main(){
	int M, N, X1, Y1, E1, N1, F1, X2, Y2, E2, N2, F2;
	scanf("%d %d %d %d %d %d %d %d %d %d %d %d", &M, &N, &X1, &Y1, &E1, &N1, &F1, &X2, &Y2, &E2, &N2, &F2);
	int step1 = 0, step2 = 0, time = 0;
	while(F1 || F2){
		time++;
		if(F1){
			F1--;
			if(step1 < N1) Y1++;
			else X1++;		
			step1++;
			step1 %= N1+E1;

			if(X1 == M) X1 %= M;
			if(Y1 == N) Y1 %= N;
		}

		if(F2){
			F2--;
			if(step2 < E2) X2++;
			else Y2++;
			step2++;
			step2 %= N2+E2;

			if(X2 == M) X2 %= M;
			if(Y2 == N) Y2 %= N;
		}

		if(X1==X2 && Y1==Y2){
			printf("robots explode at time %d\n", time);
			return 0;
		}
	}
	if(!F1 && !F2) printf("robots will not explode\n");
	return 0;
}
