#include <stdio.h>

char Map[512][512] = {0};
int N, M, L, W;

const int dir[9][2] = {0, 0, 1, 0, 0, 1, -1, 0, 0, -1, 1, 1, -1, 1, -1, -1, 1, -1};
int gx, gy;

inline int Count(const int a, const int lb, const int rb){
	int num = 0;
	for (int i=lb; i<=rb && num<2; i++)
		if (Map[a][i]==2)
			gy = a, gx = i, num++;
	return num;
}

inline int tCount(const int b, const int la, const int ra){
	int num = 0;
	for (int i=la; i<=ra && num<2; i++)
		if (Map[i][b]==2)
			gy = i, gx = b, num++;
	return num;
}

int main(){
	int num;
	scanf("%d %d %d %d %d", &N, &M, &L, &W, &num);
	for (int i=0; i<num; i++){
		int _a, _b;
		scanf("%d %d", &_a, &_b);
		Map[_b][_a] = 2;
	}

	int lx = 0, ly = 0;
	int ins;
	while (scanf("%d", &ins)!=EOF){
		int tx = lx + dir[ins][0];
		int ty = ly + dir[ins][1];
		int rx = lx + W - 1;
		int ry = ly + L - 1;
		if (ty < 0 || ty+L > N || tx < 0 || tx+W > M)
			continue;

		int num = 0;
		switch (ins){
		case 0:
			for (int i=0; i<N; i++){
				char out[512];
				for (int j=0; j<M; j++){
					if (i < ly || i > ry || j < lx || j > rx )
						out[j] = Map[i][j]+'0';
					else
						out[j] = '1';
				}
				out[M] = '\0';
				puts(out);
			}
			break;
		case 1:
			num = tCount(rx+1, ly, ry);
			break;
		case 2:
			num = Count(ry+1, lx, rx);
			break;
		case 3:
			num = tCount(lx-1, ly, ry);
			break;
		case 4:
			num = Count(ly-1, lx, rx);
			break;
		case 5:
			num = tCount(rx+1, ly+1, ry+1) + Count(ry+1, lx+1, rx);
			break;
		}
		if (num == 1) Map[gy][gx] = 0;
		else if (num) continue;

		lx = tx, ly = ty;
	}
	return 0;
}
