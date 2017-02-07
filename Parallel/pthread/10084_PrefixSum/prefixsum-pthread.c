#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "utils.h"
#include <pthread.h>
 
#define MAXN 10000005
#define MAX_THREAD 4

uint32_t prefix_sum[MAXN];
uint32_t key;
int n;
int sum[MAX_THREAD] = {0};
int threadIndex[MAX_THREAD] = {0, 1, 2, 3};

void *myReadin(void *threadID){
	int tID = *(int *)threadID;
	int l = tID*(n/MAX_THREAD)+1;
	int r = (tID==MAX_THREAD-1)? n+1: l+n/MAX_THREAD;
	uint32_t sum = 0;
	int *ptr = prefix_sum + l;
	for(int i=l; i < r; i++, ptr++){
		sum += encrypt(i, key);
		*ptr = sum;
	}
	pthread_exit(&prefix_sum[r-1]);
}

void *myPlus(void *threadID){
	int tID = *(int *)threadID;
	int l = tID*(n/MAX_THREAD)+1;
	int r = (tID==MAX_THREAD-1)? n+1: l+n/MAX_THREAD;
	int tmp = sum[tID-1];
	int *ptr = prefix_sum + l;
	if(tID != 0)
		for(int i=l; i<r; i++, ptr++){
			*ptr += tmp;
		}
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[MAX_THREAD];
    while (scanf("%d %" PRIu32, &n, &key) == 2) {
        for(int i=0; i<MAX_THREAD; i++)
			pthread_create(&threads[i], NULL, myReadin, (void *)(threadIndex+i));
		for(int i=0; i<MAX_THREAD; i++){
			int *num;
			pthread_join(threads[i], (void **)&num);
			sum[i] = *num;
		}

		for(int i=1; i<MAX_THREAD;i++)
			sum[i] += sum[i-1];
		
		for(int i=0; i<MAX_THREAD; i++)
			pthread_create(&threads[i], NULL, myPlus, (void *)(threadIndex+i));
		for(int i=0; i<MAX_THREAD; i++)
			pthread_join(threads[i], NULL);

        output(prefix_sum, n);
    }
	pthread_exit(NULL);
    return 0;
}
