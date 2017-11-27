#include <stdio.h>
#define MAXN 2048

int W[MAXN];

int main(){
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; i++)
		scanf("%d", &W[i]);

	int sum = 0, w = 0;
	for (int i=0; i<N; i++){
		sum += W[i];
		w += W[i] * i;
	}

	int sup = -1;
	for (int swap = 0; swap < N/2+1; swap++){
		if (w % sum == 0){
			sup = w / sum;
			break;
		}
		else {
			int _swap = N-1-swap;
			w -= W[swap] * swap + W[_swap] * _swap;

			int tmp = W[swap];
			W[swap] = W[_swap];
			W[_swap] = tmp;

			w += W[swap] * swap + W[_swap] * _swap;
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
