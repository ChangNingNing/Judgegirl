#include <stdio.h>
#include <stdlib.h>

int ans = 0;
int A[21] = {0};
int N, M;
void PickUp(int rest, int current, int num){
	if(current > M) return;
	if(rest<=0 && current<=M && num>=N){
		ans++;
		return;
	}
	if(num>=N) return;
	PickUp(rest-1, current+A[num], num+1);
	PickUp(rest, current, num+1);
	return;
}

int main(){
	int k;
	scanf("%d %d %d", &k, &N, &M);
	for(int i=0; i<N; i++) scanf("%d", &A[i]);
	PickUp(k, 0, 0);
	printf("%d\n", ans);
	return 0;
}
