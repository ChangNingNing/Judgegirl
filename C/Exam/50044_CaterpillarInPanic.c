#include <stdio.h>
#include <stdio.h>
#define abs(x) (((x)<0)? -1*(x): (x))

int Map[1001][1001] = {0};
int Queue[1200000][2] = {0};
int QueueF = 0, QueueL = 0;

int UpdateAndCheck(int N, int M){
	if(Queue[QueueF-1][0]<0 || Queue[QueueF-1][0]>=N) return 0;
	if(Queue[QueueF-1][1]<0 || Queue[QueueF-1][1]>=M) return 0;

	Map[Queue[QueueL-1][0]][Queue[QueueL-1][1]] = 0;
	if(Map[Queue[QueueF-1][0]][Queue[QueueF-1][1]]==1){
		Map[Queue[QueueL-1][0]][Queue[QueueL-1][1]] = 1;
		return 0;
	}
	Map[Queue[QueueF-1][0]][Queue[QueueF-1][1]] = 1;
	return 1;
}

int main(){
	int N, M, SX, SY, EX, EY, Q;
	scanf("%d %d", &N, &M);
	scanf("%d %d %d %d", &SX, &SY, &EX, &EY);
	scanf("%d", &Q);
	
	int length = abs((SX-EX)+(SY-EY)) + 1;
	int dir[2];
	dir[0] = (SX-EX!=0)? abs(SX - EX)/(SX - EX): 0;
	dir[1] = (SY-EY!=0)? abs(SY - EY)/(SY - EY): 0;
	for(int i=0; i<length; i++){
		Queue[i][0] = EX + dir[0] * i;
		Queue[i][1] = EY + dir[1] * i;
		Map[EX+dir[0]*i][EY+dir[1]*i] = 1;
	}
	QueueF = length;
	int X = SX, Y = SY;
	int isAlive = 1;
	while(Q-- && isAlive){
		int D;
		scanf("%d", &D);
		switch(D){
		case 0:
			X++;
			break;
		case 1:
			X--;
			break;
		case 2:
			Y++;
			break;
		case 3:
			Y--;
			break;
		}
		Queue[QueueF][0] = X;
		Queue[QueueF][1] = Y;
		QueueF++;
		QueueL++;
		isAlive = UpdateAndCheck(N, M);
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			printf("%d", Map[i][j]);
		}
		printf("\n");
	}
	return 0;
}
