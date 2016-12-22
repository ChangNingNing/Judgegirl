#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Swap(x, y) {int tmp=x; x=y; y=tmp;}
#define MAXN 32

int n, n_2;
int A[MAXN][2], LR[2][MAXN/2];
int max, min;

int compare(const void *a, const void *b){
	return (*(int *)a-*(int *)b);
}

int impossible(int root, int lid, int rid, int lw, int rw){
	int ll = lid+1, rr = n_2;
	for(int cur=root; cur!=-1; cur=A[cur][1]){
		if(rr > rid)
			rw += A[cur][0]*rr, rr--;
		else{
			for(int ccur=A[cur][1]; ccur!=-1; ccur=A[ccur][1])
				lw += A[ccur][0]*ll, ll++;
			break;
		}
	}
	return lw < rw;
}

int Seesaw(int root, int lid, int rid, int lw, int rw, int pos){
	if(lw == rw && lid >= n_2 && rid >= n_2) return 1;
	if(lw > rw){
		Swap(lid, rid);
		Swap(lw, rw);
		pos = !pos;
	}
	if(lid >= n_2) return 0;
	if(impossible(root, lid, rid, lw, rw)) return 0;
	int prev = -1;
	for(int cur=root, pre=-1; cur!=-1; pre=cur, cur=A[cur][1]){
		if(A[cur][0] == prev) continue;
		LR[pos][lid] = A[cur][0];
		if(cur != root){
			A[pre][1] = A[cur][1];
			if(Seesaw(root, lid+1, rid, lw+A[cur][0]*(lid+1), rw, pos)) return 1;
			A[pre][1] = cur;
		}
		else
			if(Seesaw(A[cur][1], lid+1, rid, lw+A[cur][0]*(lid+1), rw, pos)) return 1;
		prev = A[cur][0];
	}
	return 0;
}

int main(){
	while(scanf("%d", &n)==1){
		n_2 = n>>1;
		for(int i=0; i<n; i++) scanf("%d", &A[i][0]);
		qsort(A, n, sizeof(A[0]), compare);
		for(int i=0; i<n; i++) A[i][1] = i+1;
		A[n-1][1] = -1;
		max = A[n-1][0], min = A[0][0];
		if(Seesaw(0, 0, 0, 0, 0, 0)){
			for(int i=n_2-1; i>=0; i--) printf("%d ", LR[0][i]);
			printf("_^_");
			for(int i=0; i<n_2; i++) printf(" %d", LR[1][i]);
			puts("");
		}
		else printf("N\n");
	}
	return 0;
}
