#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	int nZero = 0;
	scanf("%d", &n);
	while(n--){
		int tmp;
		scanf("%d", &tmp);
		if(tmp){
			printf("%d", tmp);
			if(n!=0 || nZero!=0) printf(" ");
		}
		else nZero++;
	}
	for(int i=0; i<nZero; i++){
		printf("0");
		if(i!=nZero-1) printf(" ");
	}
	printf("\n");
	return 0;
}
