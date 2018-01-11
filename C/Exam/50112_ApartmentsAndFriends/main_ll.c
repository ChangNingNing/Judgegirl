#include <stdio.h>
#include <string.h>

#define MAXN 16

char Adj[MAXN][MAXN];
int L[MAXN][3];
int N, M;
int bound;

void myAssign(int index, int begin, int dist){
	if (index > N){
		if (dist < bound)
			bound = dist;
		return;
	}
	if (dist >= bound)
		return;

	for (int i=begin; i!=-1; i=L[i][2])
		L[i][1] <<= 1;
	int cur = begin, pre = -1;
	for (cur=begin, pre=-1; cur!=-1; pre=cur, cur=L[cur][2]){
		int tmp = dist, rest = 0, rest_f = 0;
		for (int i=0; i<N; i++){
			if (L[i][0] && Adj[cur][i])
				tmp += index - L[i][0];
			else if (!L[i][0] && i != cur){
				int tt = L[i][1]>>1, cnt = 2;
				while (tt != 0){
					if (tt & 1)
						rest += cnt;
					cnt++;
					tt >>= 1;
				}
				if (Adj[cur][i]) rest_f++;
			}
		}
		if (rest + (((rest_f+1)*rest_f)>>1) + tmp >= bound)
			continue;

		L[cur][0] = index;
		for (int i=begin; i!=-1; i=L[i][2])
			if (Adj[cur][i])
				L[i][1] += 1;
		if (cur == begin){
			myAssign( index+1, L[cur][2], tmp);
		}
		else{
			L[pre][2] = L[cur][2];
			myAssign( index+1, begin, tmp);
			L[pre][2] = cur;
		}
		L[cur][0] = 0;
		for (int i=begin; i!=-1; i=L[i][2])
			if (Adj[cur][i])
				L[i][1] -= 1;
	}
	for (int i=begin; i!=-1; i=L[i][2])
		L[i][1] >>= 1;

	return;
}

int main(){
	scanf("%d %d", &N, &M);
	for (int i=0; i<M; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		Adj[a][b] = Adj[b][a] = 1;
	}
	for (int i=0; i<N-1; i++)
		L[i][2] = i+1;
	L[N-1][2] = -1;

	bound = N * M;
	myAssign(1, 0, 0);
	printf("%d\n", bound);
	return 0;
}
