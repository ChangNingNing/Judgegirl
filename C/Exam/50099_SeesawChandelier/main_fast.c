#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#define MAXN 16384
int N;
int W[MAXN];
 
void FindBalance(int l, int r){
    if (r - l + 1 < 3) return;
    int64_t sum = 0, w = 0, b;
    for (int i=l; i<=r; i++){
        sum += W[i];
        w += W[i] * (i-l);
    }
	assert(sum != 0);
	if (w % sum != 0) return;
	b = w / sum + l;
 
    FindBalance(l, b-1);
    printf("%d\n", b);
    FindBalance(b+1, r);
}
 
int main(){
    scanf("%d", &N);
    for (int i=0; i<N; i++)
        scanf("%d", &W[i]);
    FindBalance(0, N-1);
    return 0;
}
