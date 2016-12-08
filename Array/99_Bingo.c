#include <stdio.h>
#include <stdlib.h>

int X[10][257*257] = {0};
int Y[10][257*257] = {0};
int Map[10][515] = {0};
char nameTable[10][65];

int main(){
	int n, m, i, j, k;
	scanf("%d %d", &n, &m);
	for(i=0; i<n; i++){
		scanf("%s", nameTable[i]);
		for(j=0; j<m; j++){
			for(k=0; k<m; k++){
				int temp;
				scanf("%d", &temp);
				X[i][temp] = j;
				Y[i][temp] = k;
			}
		}
	}
	int tmp;
	int winFlag = 0;
	int winner[10] = {0};
	int winnerN = 0;
	while(scanf("%d", &tmp) != EOF){
		for(i=0; i<n; i++){
			Map[i][X[i][tmp]]++;
			Map[i][Y[i][tmp]+m]++;
			if(X[i][tmp]==Y[i][tmp]) Map[i][2*m]++;
			if(X[i][tmp]+Y[i][tmp] == m-1) Map[i][2*m+1]++;

			for(j=0; j<2*m+2; j++){
				if(Map[i][j] == m){
					winner[winnerN++] = i;
					winFlag = 1;
					break;
				}
			}
		}
		if(winFlag){
			printf("%d", tmp);
			for(i=0; i<winnerN; i++){
				printf(" %s", nameTable[winner[i]]);
			}
			printf("\n");
			break;
		}
	}
	return 0;
}