#include <stdio.h>

int main(){
	int A, B, M, x;
	scanf("%d %d %d", &A, &B, &M);
	while (scanf("%d", &x)!=EOF){
		if (M == 0){
			if (x <= A) A -= x;
			else if (x <= B) B -= x;
		}
		else {
			if (A <= B){
				if (x <= A) A -= x;
				else if (x <= B) B -= x;
			}
			else {
				if (x <= B) B -= x;
				else if (x <= A) A -= x;
			}
		}
		printf("%d %d\n", A, B);
	}
	return 0;
}
