#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char A[51][12];
char TeamL[3][12];
int Team[3][51] = {0};
int nTeam[3] = {0};
int N, L, R;

int Dist(char *X, char *Y){
	int sum = 0;
	for(int i=0; i<L; i++) sum += abs(X[i] - Y[i]);
	return sum;
}

int Compare(const void *a, const void *b){
	return strcmp((char *)a, (char *)b);
}

int Compare2(const void *a, const void *b){
	return *(int *)a - *(int *)b;
}

int main(){
	scanf("%d %d %d", &N, &L, &R);
	for(int i=0; i<N; i++) scanf("%s", A[i]);
	for(int i=0; i<3; i++) strcpy(TeamL[i], A[i]);
	qsort(A, N, sizeof(A[0]), Compare);
	qsort(TeamL, 3, sizeof(TeamL[0]), Compare);
	for(int i=0, j=0; i<N; i++){
		if(strcmp(TeamL[j], A[i])==0)
			Team[j++][0] = i;
	}

	for(R; R>0; R--){
		nTeam[0] = nTeam[1] = nTeam[2] = 1;
		for(int i=0; i<N; i++){
			int dist, minD = 10000, minDP = -1;
			for(int j=0; j<3; j++){
				dist = Dist(A[i], A[Team[j][0]]);
				if(dist < minD){
					minD = dist;
					minDP = j;
				}
			}
			Team[minDP][nTeam[minDP]++] = i;
		}
		for(int i=0; i<3; i++){
			int tmpDim[12] = {0};
			char meanDim[12];
			for(int j=1; j<nTeam[i]; j++){
				for(int k=0; k<L; k++){
					tmpDim[k] += A[Team[i][j]][k];
				}
			}
			for(int k=0; k<L; k++) meanDim[k] = tmpDim[k] / (nTeam[i]-1);
			int dist, minD = 10000, minDP = -1;
			for(int j=1; j<nTeam[i]; j++){
				dist = Dist(A[Team[i][j]], meanDim);
				if(dist < minD){
					minD = dist;
					minDP = j;
				}
			}
			Team[i][0] = Team[i][minDP];
		}
		qsort(Team, 3, sizeof(Team[0]), Compare2);
	}
	for(int i=0; i<3; i++) puts(A[Team[i][0]]);
	return 0;
}
