#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *T[1024][1024];
char S[16384][1024];

int main(){
	int N;
	scanf("%d", &N);
	int nW = 0;
	for (int i=0; i<N; i++){
		char _t;
		int _w = 0;
		while (scanf("%s%c", S[nW], &_t) == 2){
			T[i][_w] = S[nW];
			nW++, _w++;
			if (_t == '\n')
				break;
		}
		T[i][_w] = NULL;
	}

	int M;
	scanf("%d", &M);
	for (int i=0; i<M; i++){
		int l1, w1, l2, w2;
		scanf("%d %d %d %d", &l1, &w1, &l2, &w2);
		char *tmp = T[l1][w1];
		T[l1][w1] = T[l2][w2];
		T[l2][w2] = tmp;
	}

	for (int i=0; i<N; i++, puts("")){
		for (int j=0; T[i][j]!=NULL; j++){
			if (j==0)
				printf("%s", T[i][j]);
			else
				printf(" %s", T[i][j]);
		}
	}
	return 0;
}
