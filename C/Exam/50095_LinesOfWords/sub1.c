#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char T[1024][1024][1024];

int main(){
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		int nW = 0;
		char _t;
		while (scanf("%s%c", T[i][nW], &_t) == 2){
			nW++;
			if (_t == '\n')
				break;
		}
		T[i][nW][0] = '\0';
	}

	int M;
	scanf("%d", &M);
	for (int i=0; i<M; i++){
		int l1, w1, l2, w2;
		scanf("%d %d %d %d", &l1, &w1, &l2, &w2);
		char tmp[1024];
		strcpy(tmp, T[l1][w1]);
		strcpy(T[l1][w1], T[l2][w2]);
		strcpy(T[l2][w2], tmp);
	}

	for (int i=0; i<N; i++, puts("")){
		for (int j=0; T[i][j][0]!='\0'; j++){
			if (j==0)
				printf("%s", T[i][j]);
			else
				printf(" %s", T[i][j]);
		}
	}
	return 0;
}
