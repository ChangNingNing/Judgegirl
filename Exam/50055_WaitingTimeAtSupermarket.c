#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CounterMax 1024
int Counters[CounterMax] = {0};

int main(){
	int N, M, sum = 0;
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++){
		int time, spend, flag = 0;;
		scanf("%d %d", &time, &spend);
		int min = INT_MAX, minP = -1;
		for(int j=0; j<N; j++){
			if(Counters[j] <= time){
				Counters[j] = time + spend;
				flag = 1;
				break;
			}
			if(Counters[j] < min){
				min = Counters[j];
				minP = j;
			}
		}
		if(flag) continue;
		sum += min - time;
		Counters[minP] += spend;
	}
	printf("%d\n", sum);
	return 0;
}
