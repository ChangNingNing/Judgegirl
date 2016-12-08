#include <stdio.h>
#include <stdlib.h>

int coin[7] = {1000, 500, 100, 50, 10, 5, 1};

int main(){
	int money;
	while(scanf("%d", &money)!=EOF){
		int nCoin[7] = {0};
		for(int i=0; i<7; i++){
			if(money>=coin[i]){
				nCoin[i] = money / coin[i];
				money %= coin[i];
			}
		}
		for(int i=0; i<7; i++){
			if(i!=0) printf(" ");
			printf("%d", nCoin[i]);
		}
		printf("\n");
	}
}
