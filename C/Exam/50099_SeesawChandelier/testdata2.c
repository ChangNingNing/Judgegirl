#include <stdio.h>
#include <assert.h>
#define MAXN 35
int W[MAXN];

int main(){
	int nW, isB;
	W[0] = W[1] = 0;
	W[2] = 1;
	isB = 1;
	nW = 3;
	for (int i=nW; i<MAXN; i++){
		if (isB){
			W[nW] = 1;
			isB = 0;
		}
		else {
			int sum = 0;
			for (int i=0; i<nW-1; i++)
				sum += W[i] * (nW-1-i);
			W[nW] = sum;
			sum += W[nW] + W[nW - 1];
			isB = 1;
		}
		nW++;
	}
	printf("%d\n", nW);
	for (int i=0; i<nW; i++)
		printf("%d%c", W[i], " \n"[i==nW-1]);
	return 0;
}
