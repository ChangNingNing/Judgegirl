#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int A[16] = {0};
int map[65536] = {0};

void Subset(int n, int bit){
	if(bit >= pow(2, n)) return;
	int sum = 0;
	for(int i=0; i<16; i++){
		if((bit>>i) & 1) sum += A[i];
	}
	map[sum]++;
	Subset(n, bit+1);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", &A[i]);
	Subset(n, 0);	
	int input;
	while(scanf("%d", &input)!=EOF){
		printf("%d\n", map[input]);
	}
	return 0;
}
