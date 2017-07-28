#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define MAXN 65536

int X, Y, D, N, T;
int pos[MAXN][2];

int main(int argc, char *argv[]){
	if (argc < 6){
		puts("argc is not correct");
		exit(0);
	}

	X = atoi(argv[1]);
	Y = atoi(argv[2]);
	D = atoi(argv[3]);
	N = atoi(argv[4]);
	T = atoi(argv[5]);

	printf("%d %d %d\n", X, Y, D);
	printf("%d %d\n", N, T);

	srand(time(NULL));

	for (int i=0; i<N; i++){
		pos[i][0] = rand() % (X+1);
		pos[i][1] = rand() % (Y+1);
		printf("%d %d%c", pos[i][0], pos[i][1], i!=N-1? ' ': '\n');
	}

	for (int t=1; t<T; t++){
		for (int i=0; i<N; i++){
			int dir[2];
			dir[0] = rand() % 7 - 3;
			dir[1] = rand() % 7 - 3;
			if (dir[0] > 0 && pos[i][0] + dir[0] > X) dir[0] = X - pos[i][0];
			if (dir[0] < 0 && pos[i][0] + dir[0] < 0) dir[0] = 0 - pos[i][0];
			if (dir[1] > 0 && pos[i][1] + dir[1] > Y) dir[1] = Y - pos[i][1];
			if (dir[1] < 0 && pos[i][1] + dir[1] < 0) dir[1] = 0 - pos[i][1];

			pos[i][0] += dir[0];
			pos[i][1] += dir[1];

			printf("%d %d%c", dir[0], dir[1], i!=N-1? ' ': '\n');
		}
	}
}
