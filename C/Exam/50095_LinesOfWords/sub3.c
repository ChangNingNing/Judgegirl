#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **F[1024];
char *S[16384];
char W[10000000];
int nF[1024];

int main(){
	int N;
	scanf("%d", &N);
	int nW = 0, pos = 0;
	for (int i=0; i<N; i++){
		char _t;
		F[i] = &S[nW];
		while (scanf("%s%c", &W[pos], &_t)==2){
			S[nW] = &W[pos];
			nW++;
			nF[i]++;
			pos += strlen(&W[pos]) + 1;
			if (_t == '\n')
				break;
		}
	}

	int M;
	scanf("%d", &M);
	for (int i=0; i<M; i++){
		int l1, w1, l2, w2;
		scanf("%d %d %d %d", &l1, &w1, &l2, &w2);
		char *tmp = F[l1][w1];
		F[l1][w1] = F[l2][w2];
		F[l2][w2] = tmp;
	}

	for (int i=0; i<N; i++, puts("")){
		for (int j=0; j<nF[i]; j++){
			if (j==0)
				printf("%s", F[i][j]);
			else
				printf(" %s", F[i][j]);
		}
	}
	return 0;
}
