#include <stdio.h>
#include <stdlib.h>

int M[4][4];
int n;
int Awin, Bwin, AB;

void Game(int player, int set, int Ascore, int Bscore){
	int flag = 0;
	switch(player){
	case 0:
		for(int i=0; i<n; i++){
			if(M[set][i]>=0){
				flag = 1;
				int score = M[set][i];
				M[set][i] = -1;
				Ascore += score;
				Game(1, i, Ascore, Bscore);
				Ascore -= score;
				M[set][i] = score;
			}
		}
		break;
	case 1:
		for(int i=0; i<n; i++){
			if(M[i][set]>=0){
				flag = 1;
				int score = M[i][set];
				M[i][set] = -1;
				Bscore += score;
				Game(0, i, Ascore, Bscore);
				Bscore -= score;
				M[i][set] = score;
			}
		}
		break;
	}
	if(flag) return;
	if(Ascore > Bscore) Awin++;
	else if(Ascore < Bscore) Bwin++;
	else AB++;
	return;
}

int main(){
	while(scanf("%d", &n)!=EOF){
		Awin = Bwin = AB = 0;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				scanf("%d", &M[i][j]);
			}
		}
		Game(0, 0, 0, 0);
		printf("%d %d %d\n", Awin, Bwin, AB);
	}
	return 0;
}
