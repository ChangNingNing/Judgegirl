#include <stdio.h>
#include <stdlib.h>

int Map[1002][1002] = {0};
int Ans[10000000][2] = {0};
int nAns = 0;

int main(){
	int N, M, Q;
	scanf("%d %d", &N, &M);
	scanf("%d", &Q);
	while(Q--){
		int lx, ly, rx, ry;
		nAns = 0;
		scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
		for(int i=lx; i<=rx; i++){
			for(int j=ly; j<=ry; j++){
				if(!Map[i][j]){
					Map[i][j] = 1;
					Ans[nAns][0] = i;
					Ans[nAns][1] = j;
					nAns++;
				}
			}
		}
		printf("%d", nAns);
		for(int i=0; i<nAns; i++) printf(" (%d, %d)", Ans[i][0], Ans[i][1]);
		printf("\n");
	}
	return 0;
}
