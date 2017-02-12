#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAXN 4096
#define LL long long int
LL DP[MAXN*MAXN], SZ[MAXN+1];
int N;

int main(){
	while(scanf("%d", &N)==1){
		for(int i=0; i<N; i++)
			scanf("%lld", &SZ[i]), DP[i*N+i] = 0;
		scanf("%lld", &SZ[N]);

		#pragma omp parallel
		for(int l=1; l<N; l++){
			#pragma omp for
			for(int i=0; i < N-l; i++){
				int j = i + l;
				LL min = 0x7fffffffffffffff, SZtmp = SZ[i]*SZ[j+1];
				LL *ptr1 = DP+i*N, *ptr2 = DP+j*N;
				for(int k=i; k<j; k++){
					LL tmp = ptr1[k] + ptr2[k+1] + SZtmp * SZ[k+1];
					if(tmp < min) min = tmp; 
				}
				ptr1[j] = ptr2[i] = min;
			}
		}
		printf("%lld\n", DP[N-1]);
	}
	return 0;
}
