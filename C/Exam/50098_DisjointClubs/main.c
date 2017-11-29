#include <stdio.h>
#include <stdint.h>
#define MAXN 101
int N, K;
uint64_t M[MAXN];
uint64_t dM[MAXN][2];
int8_t isPick[MAXN];

int Pick(int club, int rest, uint64_t s1, uint64_t s2){
	if (rest <= 0) return 1;
	if (__builtin_popcountll(s1) + __builtin_popcountll(s2) < rest) return 0;

	if (club < 64 && ((s1>>club) & 1)){
		if (Pick(club+1, rest-1, s1 & dM[club][0], s2 & dM[club][1]))
			return isPick[club] = 1;
		return Pick(club+1, rest, s1 - (1LLU<<club), s2);
	}
	else if (club >= 64 && ((s2>>(club-64)) & 1)){
		if (Pick(club+1, rest-1, s1 & dM[club][0], s2 & dM[club][1]))
			return isPick[club] = 1;
		return Pick(club+1, rest, s1, s2 - (1LLU<<(club-64)));
	}
	return Pick(club+1, rest, s1, s2);
}

int main(){
	scanf("%d %d", &N, &K);
	for (int i=0; i<N; i++){
		int n;
		scanf("%d", &n);
		for (int j=0; j<n; j++){
			int t;
			scanf("%d", &t);
			M[i] |= 1LLU << t;
		}
	}
	for (int i=0; i<N; i++){
		for (int j = i+1; j<N; j++){
			if (!(M[i] & M[j])){
				if (j < 64) dM[i][0] |= 1LLU << j;
				else dM[i][1] |= 1LLU << (j - 64);
				if (i < 64) dM[j][0] |= 1LLU << i;
				else dM[j][1] |= 1LLU << (i - 64);
			}
		}
	}

	uint64_t s1 = 0, s2 = 0;
	for (int i=0; i<N; i++){
		if (i < 64) s1 |= 1LLU << i;
		else s2 |= 1LLU << (i-64);
	}
	Pick(0, K, s1, s2);
	for (int i=0; i<N; i++)
		if (isPick[i]) printf("%d\n", i);
	return 0;
}
