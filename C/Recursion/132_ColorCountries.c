#include <stdio.h>
#include <stdlib.h>

int Map[21][21] = {0};
int Color[21] = {0};
int N, C, P;

int Paint(int root, int pre){
//printf("root = %d\n", root);
//fflush(stdout);
	if(Color[root]!=0) return 1;
	for(int i=1; i<=C; i++){
		int flag = 0;
		Color[root] = i;
		for(int j=0; j<N; j++){
			if(Map[root][j] && Color[j]==i){
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		int ans = 1;
		for(int j=0; j<N; j++){
			if(Map[root][j] && j!=pre){
				ans &= Paint(j, root);
				if(!ans) break;
			}
		}
		if(ans) return 1;
		else continue;
	}
	Color[root] = 0;
	return 0;
}

int main(){
	scanf("%d %d %d", &N, &C, &P);
	while(P--){
		int x, y;
		scanf("%d %d", &x, &y);
		Map[x][y] = 1;
		Map[y][x] = 1;
	}
	int ans = 1;
	for(int i=0; i<N; i++){
		if(Color[i]==0 && ans) ans &= Paint(i, -1);
	}
	if(ans){
		for(int i=0; i<N; i++) printf("%d\n", Color[i]);
	}
	else printf("no solution.\n");
}
