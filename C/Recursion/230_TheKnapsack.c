#include <stdio.h>
#include <stdlib.h>

int w[21] = {0};
int v[21] = {0};
int n;
int max = 0;

void knapsack(int weight, int value, int index){
	if(weight<0) return;
	if(index > n) return;
	if(weight>=0){
		if(value > max) max = value;
	}
	knapsack(weight-w[index], value+v[index], index+1);
	knapsack(weight, value, index+1);
}

int main(){
	int W;
	scanf("%d %d", &n, &W);
	for(int i=0; i<n; i++)
		scanf("%d %d", &w[i], &v[i]);
	knapsack(W, 0, 0);
	printf("%d\n", max);
	return 0;
}
