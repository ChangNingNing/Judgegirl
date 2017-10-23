#include "travel.h"

const int D[8][2] = { 0, 1, 0, -1, 1, 0, -1, 0, 1, 1, -1, -1, -1, 1, 1, -1};
char rec[1024][1024];

int findMax(int map[1024][1024], int N, int M, int r, int c){
	int max = 0, maxD = -1;
	for (int i=0; i<8; i++){
		int _r = r + D[i][0];
		int _c = c + D[i][1];
		if (_r >= 0 && _r < N && _c >= 0 && _c < M){
			if (map[_r][_c] - map[r][c] > max){
				max = map[_r][_c] - map[r][c];
				maxD = i;
			}
		}
	}
	return maxD;
}

int findMin(int map[1024][1024], int N, int M, int r, int c){
	int max = 0, maxD = -1;
	for (int i=0; i<8; i++){
		int _r = r + D[i][0];
		int _c = c + D[i][1];
		if (_r >= 0 && _r < N && _c >= 0 && _c < M){
			if (map[r][c] - map[_r][_c] > max){
				max = map[r][c] - map[_r][_c];
				maxD = i;
			}
		}
	}
	return maxD;
}

void travel(int map[1024][1024], int N, int M, int ar, int ac, int br, int bc, int TA[], int TB[]){
	int an = 0, bn = 0;
	int ad = 0, bd = 0;
	rec[ar][ac] = rec[br][bc] = 1;
	while (ad != -1 || bd != -1){
		ad = ad!=-1? findMax(map, N, M, ar, ac): -1;
		bd = bd!=-1? findMin(map, N, M, br, bc): -1;

		if (ad >= 0){
			ar += D[ad][0];
			ac += D[ad][1];
			TA[an++] = ad;

			if (rec[ar][ac])
				ad = -1;
			else
				rec[ar][ac] = 1;
		}
		if (bd >= 0){
			br += D[bd][0];
			bc += D[bd][1];
			TB[bn++] = bd;

			if (rec[br][bc])
				bd = -1;
			else
				rec[br][bc] = 1;
		}

		if (ar==br && ac==bc)
			ad = -1, bd = -1;
	}
	TA[an] = -1, TB[bn] = -1;
	return;
}
