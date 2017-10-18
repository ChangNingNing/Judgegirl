#include <stdio.h>
#include <assert.h>
#define MAXN 2048

int W[MAXN];

int main(){
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; i++)
		scanf("%d", &W[i]);

	int noAns = 1;
	int sup = -1;
	int swap = 0;
	while (noAns){
		// The first step
		for (int i=1; i<N-1 && noAns; i++){
			int lw = 0, rw = 0;
			for (int j=0; j<i; j++)
				lw += W[j] * (i - j);
			for (int j=i+1; j<N; j++)
				rw += W[j] * (j - i);
			if (lw == rw){
				sup = i;
				noAns = 0;

				// Check balance
//				printf("lw == rw == %d\n", lw);
			}
			// Check overflow
//			assert(lw > 0 && rw > 0);
		}

		// The second step
		if (noAns){
			int tmp = W[swap];
			W[swap] = W[N-1-swap];
			W[N-1-swap] = tmp;
			swap++;
		}

		// Check answer
//		if (swap >= N / 2 + 1){
//			printf("N\n");
//			return 0;
//		}
	}

	// Check swap
//	printf("swap == %d\n", swap);

	for (int i=0; i<N; i++){
		if (i!=sup)
			printf("%d%c", W[i], i!=N-1? ' ': '\n');
		else
			printf("v ");
	}
	return 0;
}
