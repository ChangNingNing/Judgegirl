#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#define MAXN 16384
int N, M;
int W[MAXN];

void FindBalance(int l, int r){
	if (r - l + 1 < 3) return;
	int b;
	for (b=l; b<=r; b++){
		int64_t wl = 0, wr = 0;
		for (int i=l; i<b; i++) wl += W[i] * (b - i);
		for (int i=b+1; i<=r; i++) wr += W[i] * (i - b);
		assert(wl >= 0 && wr >= 0);
		if (wl == wr) break;
	}
	if (b == r+1) return;
	int flag = 0;
	for (int i=l; i<=r; i++){
		if (W[i] != 0) flag = 1;
	}
	assert(flag == 1);

	FindBalance(l, b-1);
	printf("%d\n", b);
	FindBalance(b+1, r);
	return;
}

int main(){
	scanf("%d", &N);
	for (int i=0; i<N; i++)
		scanf("%d", &W[i]);
	FindBalance(0, N-1);
	return 0;
}
