#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 64

int N, M;
int bound = 0;
int Donation[MAXN] = {0};
unsigned long long int Hate[MAXN] = {0};

void IndependentSet(int index, int money, unsigned long long int canSelect){
	if(index >= N){
		if(money > bound) bound = money;
		return;
	}

	int tmpMoney = 0;
	for(int i=index; i<N; i++){
		if((canSelect >> i) & 1) continue;
		tmpMoney += Donation[i];
	}
	if(tmpMoney + money <= bound) return;

	if(((canSelect >> index) & 1) == 0)
		IndependentSet(index + 1, money + Donation[index], canSelect | Hate[index]);
	IndependentSet(index + 1, money, canSelect);
	return;
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++)
		scanf("%d", &Donation[i]);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			int a;
			scanf("%d", &a);
			if(a == 1)
				Hate[i] |= ((unsigned long long int)1 << j);
		}
	}
	IndependentSet(0, 0, 0);
	printf("%d\n", bound);
	return 0;
}
