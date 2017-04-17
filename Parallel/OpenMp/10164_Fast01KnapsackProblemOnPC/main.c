#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <assert.h>


#define MAXN 10005
#define MAXM 5000005

int N, M;
int obj[MAXN][2];
int sub[2][MAXN][2] = {0}, pSum[2][MAXN] = {0}, n[2] = {0};
int DP[2][MAXM] = {0};

int MAX(int a, int b){ return a>b? a: b; }
int MIN(int a, int b){ return a<b? a: b; }

int myComp(const void *a, const void *b){
	return *(int *)a - *(int *)b;
}

void knapsack(int flag){
	int *_DP = DP[flag], *_pSum = pSum[flag];
	int _n = n[flag];
	for (int i=0; i<_n; i++)
		for (int j=MIN(_pSum[i+1], M); j>=0; j--)
			if (j >= sub[flag][i][0])
				_DP[j] = MAX(_DP[j], _DP[j-sub[flag][i][0]] + sub[flag][i][1]);
	for (int i=1; i<=M; i++)
		if (_DP[i] == 0) _DP[i] = _DP[i-1];
}

int main(){
	omp_set_num_threads(2);
    #pragma omp parallel
    {
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        for (int i = 0; i < 6; i++)
            CPU_SET(i, &cpuset);
        assert(sched_setaffinity(0, sizeof(cpuset), &cpuset) == 0);
    }

	scanf("%d %d", &N, &M);
	for (int i=0; i<N; i++)
		scanf("%d %d", &obj[i][0], &obj[i][1]);
	qsort(obj, N, sizeof(obj[0]), myComp);

	for (int i=0; i<N; i++){
		int flag;
		if (pSum[0][n[0]] >= pSum[1][n[1]]) flag = 1;
		else flag = 0;
		sub[flag][n[flag]][0] = obj[i][0];
		sub[flag][n[flag]][1] = obj[i][1];
		pSum[flag][n[flag]+1] = pSum[flag][n[flag]] + sub[flag][n[flag]][0];
		n[flag]++;
	}

	#pragma omp parallel sections
	{
		#pragma omp section
		{
		knapsack(0);
		}
		#pragma omp section
		{
		knapsack(1);
		}
	}

	int tmpMax = DP[1][0];
	int ret = DP[0][M];
	for (int i=M, j=0; i>=0, j<=M; i--, j++){
		tmpMax = MAX(DP[1][j], tmpMax);
		ret = MAX(DP[0][i]+tmpMax, ret);
	}
	printf("%d\n", ret);
	return 0;
}
