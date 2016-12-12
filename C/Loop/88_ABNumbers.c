#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j;
	char A[5], B[5];
	int a=0, b=0;
	scanf("%s %s", A, B);
	for(i=0; i<4; i++){
		if(A[i]==B[i])
			a++;
		else{
			for(j=0; j<4; j++){
				if(A[i]==B[j]) b++;
			}
		}
	}

	printf("%dA%dB\n", a, b);
	return 0;
}
