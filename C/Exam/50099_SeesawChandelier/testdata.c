#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#define MAXN 16384
int W1[MAXN], W2[MAXN], W3[MAXN];
int n = 0;

int FindBalance(int *W, int l, int r){
	int b;
	for (b=l+1; b<r-1; b++){
		int64_t wl = 0, wr = 0;
		for (int i=l; i<b; i++) wl += W[i] * (b-i);
		for (int i=b+1; i<r; i++) wr += W[i] * (i-b);
		if (wl == wr) break;
	}
	return b;
}

int GCD(int a, int b){
	int c;
	while (a != 0){
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

int main(){
	int N1, N2, b1, b2, l1 , l2;
	int64_t w1, w2, s1, s2;
	w1 = w2 = s1 = s2 = 0;
	scanf("%d %d", &N1, &l1);
	for (int i=0; i<N1; i++){
		scanf("%d", &W1[i]);
		w1 += W1[i] * (N1 - i);
		s1 += W1[i];
	}
	scanf("%d %d", &N2, &l2);
	for (int i=0; i<N2; i++){
		scanf("%d", &W2[i]);
		w2 += W2[i] * (i + 1);
		s2 += W2[i];
	}
	assert(l1 == l2);

	b1 = FindBalance(W1, 0, N1);
	b2 = FindBalance(W2, 0, N2);

	int gcd = GCD(s1, s2);
	int r1 = s2 / gcd, r2 = s1 / gcd;
	while (r1 - (N1 - b1) < 0 || r2 - (b2 + 1) < 0)
		r1 *= 2, r2 *= 2;

	srand(time(NULL));
	for (int i=0; i<N1; i++) W3[n++] = W1[i];
	for (int i=0; i<r1-(N1-b1); i++) W3[n++] = 0;
	W3[n++] = rand() % 1024;
	for (int i=0; i<r2-(b2+1); i++) W3[n++] = 0;
	for (int i=0; i<N2; i++) W3[n++] = W2[i];

	/*
	printf("%d %lld %lld %d\n", N1, s1, w1, b1);
	printf("%d %lld %lld %d\n", N2, s2, w2, b2);
	printf("gcd = %d, %d %d\n", gcd, r1, r2);
	*/

	printf("%d %d\n", n, l1+1);
	for (int i=0; i<n; i++) printf("%d%c", W3[i], " \n"[i==n-1]);
	return 0;
}
