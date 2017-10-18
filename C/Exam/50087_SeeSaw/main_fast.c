#include <stdio.h>
#define MAXN 2048

int W[MAXN];
int S[MAXN];

int main(){
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; i++)
		scanf("%d", &W[i]);

	for (int i=0; i<N; i++){
		int cur = W[i];
		for (int j=i-1; j>=0; j--){
			S[j] += cur;
			cur += W[i];
		}
		cur = W[i];
		for (int j=i+1; j<N; j++){
			S[j] -= cur;
			cur += W[i];
		}
	}

	int sup = -1;
	int noAns = 1;
	for (int swap = 0; swap < N/2+1 && noAns; swap++){
		/*
		for (int i=1; i<N-1 && noAns; i++){
			if (S[i] == 0){
				sup = i;
				noAns = 0;
			}
		}
		*/
		{
			int l = 1, r = N-2;
			while (l <= r){
				int mid = (l + r) / 2;
				if (S[mid] <= 0) r = mid - 1;
				else l = mid + 1;
			}
			if (S[l] == 0){
				sup = l;
				noAns = 0;
			}
		}

		if (noAns){
			int _swap = N-1-swap;
			for (int i=0; i<N; i++){
				if (i < swap)
					S[i] += W[swap]*(_swap-swap) + W[_swap]*(swap-_swap);
				else if (i == swap)
					S[i] += W[swap]*(_swap-i) - W[_swap]*(_swap-i);
				else
					S[i] += W[swap]*(_swap-swap) - W[_swap]*(_swap-swap);
			}

			int tmp = W[swap];
			W[swap] = W[_swap];
			W[_swap] = tmp;
		}
	}

	for (int i=0; i<N; i++){
		if (i != sup)
			printf("%d%c", W[i], i!=N-1? ' ': '\n');
		else
			printf("v ");
	}

	return 0;
}
