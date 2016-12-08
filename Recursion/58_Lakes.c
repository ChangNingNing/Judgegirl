#include <stdio.h>
#include <stdlib.h>

int N, M;
int Map[402][402][2] = {0};
int answer[402*402/2+1] = {0};
int answerN = 0;

int compare(const void *a, const void *b){
	return *(int *)b-*(int *)a;
}

int Lake(int x, int y) {
	if (Map[x][y][0] == 0 || Map[x][y][1] == 1)
		return 0;
	Map[x][y][1] = 1;
	int ret = 0;
	ret += Lake(x+1, y);
	ret += Lake(x-1, y);
	ret += Lake(x, y+1);
	ret += Lake(x, y-1);
	return ret+1;
}

int main(){
	scanf("%d %d", &N, &M);
	for(int i=1; i<=N; i++){
		for(int j=1; j<=M; j++){
			scanf("%d", &Map[i][j][0]);
		}
	}

	for(int i=1; i<=N; i++){
		for(int j=1; j<=M; j++){
			if(Map[i][j][0] && !Map[i][j][1]){
				answer[answerN] = Lake(i, j);
				answerN++;
			}
		}
	}
	qsort((void *)answer, answerN, sizeof(answer[0]), compare);
	for(int i=0; i<answerN; i++){
		printf("%d\n", answer[i]);
	}
	return 0;
}
