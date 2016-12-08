#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CounterMax 1024
int Counters[CounterMax+1] = {0};

void bubbleDown(int index, int size){
	for(int i=index*2; i<=size; i*=2){
		if(i+1<=size && Counters[i+1] < Counters[i]) i++;
		if(Counters[i] < Counters[i/2]){
			int tmp = Counters[i];
			Counters[i] = Counters[i/2];
			Counters[i/2] = tmp;
		}
		else break;
	}
}

void bubbleUp(int index, int size){
	for(int i=index; i>1; i/=2){
		if(Counters[i/2] > Counters[i]){
			int tmp = Counters[i];
			Counters[i] = Counters[i/2];
			Counters[i/2] = tmp;
		}
		else break;
	}
}

int main(){
	int N, M, sum = 0;
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++){
		int time, spend;
		scanf("%d %d", &time, &spend);
		int minTime = Counters[1];
		Counters[1] = Counters[N];
		bubbleDown(1, N-1);
		
		if(minTime <= time){
			minTime = time + spend;
		}
		else{
			sum += minTime - time;
			minTime += spend;
		}
		
		Counters[N] = minTime;
		bubbleUp(N, N);
	}
	printf("%d\n", sum);
	return 0;
}
