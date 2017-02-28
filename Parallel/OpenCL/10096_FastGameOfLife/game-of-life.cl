#define MAXN 2003
__kernel void GameLife(int N, int turn, __global char T[2][MAXN*MAXN]){
	int globalID = get_global_id(0);
	int r = globalID / N + 1, c = globalID % N + 1;
	int wf = turn&1, rf = 1 - wf, n = N+2;
	int nLive = T[rf][(r-1)*n+(c-1)] + T[rf][(r-1)*n+c] + T[rf][(r-1)*n+(c+1)] +
				T[rf][r*n+(c-1)] 						+ T[rf][r*n+(c+1)] +
				T[rf][(r+1)*n+(c-1)] + T[rf][(r+1)*n+c] + T[rf][(r+1)*n+(c+1)];
	T[wf][r*n+c] = T[rf][r*n+c]? nLive==2 || nLive==3: nLive==3;
}
