#include <stdio.h>
#include <stdlib.h>

/*1 for black; 2 for white*/
int T[4][4] = {0};

int main(){
	int move, i, j, turn = 0;
	scanf("%d", &move);
	int winflag = 0;
	for(i=0; i<move; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		if(x<0 || x>2 || y<0 || y>2) continue;
		if(T[x][y]) continue;
		if(turn==0){
			T[x][y] = 1;
			T[x][3]++;
			T[3][y]++;
			if(x==y) T[3][3]++;
			turn++;
		}
		else{
			T[x][y] = 2;
			T[x][3] += 10;
			T[3][y] += 10;
			if(x==y) T[3][3] += 10;
			turn = 0;
		}
		for(j=0; j<3; j++){
			if(T[j][3]==3){
				printf("Black wins.\n");
				winflag = 1;
			}
			if(T[3][j]==3){
				printf("Black wins.\n");
				winflag = 1;
			}
			if(T[j][3]==30){
				winflag = 1;
				printf("White wins.\n");
			}
			if(T[3][j]==30){
				winflag = 1;
				printf("White wins.\n");
			}
		}
		if(T[3][3]==3){
			winflag = 1;
			printf("Black wins.\n");
		}
		if(T[3][3]==30){
			winflag = 1;
			printf("White wins.\n");
		}
		if(T[0][2]==1 && T[1][1]==1 && T[2][0]==1){
			winflag = 1;
			printf("Black wins.\n");
		}
		if(T[0][2]==2 && T[1][1]==2 && T[2][0]==2){
			winflag = 1;
			printf("White wins.\n");
		}
		if(winflag) break;
	}
	if(!winflag) printf("There is a draw.\n");
	return 0;
}