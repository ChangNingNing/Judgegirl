#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "utils.h"
#include <omp.h>
 
#define MAXN 10000005

uint32_t prefix_sum[MAXN];
int nThreads = 4;

int Min(int a, int b) { return a < b? a: b; }

int main() {
	int n;
	uint32_t key;
    while (scanf("%d %" PRIu32, &n, &key) == 2) {
		int chunk = (n + nThreads - 1) / nThreads;
		int sum[nThreads];
		#pragma omp parallel for
		for(int i=0; i<nThreads; i++){
			int l = i * chunk + 1, r = Min(l + chunk, n+1);
			uint32_t tmp = 0;
			int *ptr = prefix_sum + l;
			for(int j=l; j<r; j++, ptr++){
				tmp += encrypt(j, key);
				*ptr = tmp;
			}
			sum[i] = prefix_sum[r-1];
		}

		for(int i=1; i<nThreads; i++)
			sum[i] += sum[i-1];

		#pragma omp parallel for
		for(int i=1; i<nThreads; i++){
			int l = i*chunk+1, r = Min(l + chunk, n+1);
			int tmp = sum[i-1];
			int *ptr = prefix_sum + l;
			for(int j=l; j<r; j++, ptr++)
				*ptr += tmp;
		}
        output(prefix_sum, n);
    }
    return 0;
}
