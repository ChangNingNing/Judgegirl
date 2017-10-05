#include <stdio.h>
#include <limits.h>

int Job[512] = {0}, Machine[512] = {0};
int T[512][512][2] = {0};
int ptrT[512] = {0};

int Max(int a, int b){ return a>b? a: b; }

int main(){
	int N, M, nT = 0;
	scanf("%d %d", &N, &M);
	for (int i=0; i<M; i++){
		int tmp;
		scanf("%d %d", &Job[i], &tmp);
		for (int j=0; j<tmp; j++)
			scanf("%d %d", &T[i][j][0], &T[i][j][1]);
		T[i][tmp][0] = T[i][tmp][1] = -1;
		nT += tmp;
	}

	for (int i=0; i<nT; i++){
		int min = INT_MAX, minJ = -1, minM = -1;
		for (int j=0; j<M; j++){
			int m = T[j][ptrT[j]][0], t = T[j][ptrT[j]][1];
			if (m < 0) continue;
			if (Max(Job[j], Machine[m]) + t < min){
				min = Max(Job[j], Machine[m]) + t;
				minJ = j;
				minM = m;
			}
		}
		Job[minJ] = min;
		Machine[minM] = min;
		ptrT[minJ]++;
	}

	for (int i=0; i<M; i++)
		printf("%d\n", Job[i]);
	return 0;
}
