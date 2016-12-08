#include <stdio.h>
#include <stdlib.h>

int A[100000] = {0};

int main(){
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		int tmp;
		scanf("%d", &tmp);
		A[tmp]++;
		if(A[tmp]>1){
			printf("%d\n", tmp);
			break;
		}
	}
	return 0;
}
