#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <assert.h>
#define MAXN 20
#define MAXQ (1<<16)

int isOccu[MAXN];

typedef struct {
	int row, d1, d2, next;
} Node;
Node node[2][MAXQ];

int n, c = 0;

int queen (int row, int d1, int d2, int next){
    if(next >= n) return 1;
    int sum = 0;
	int mask = isOccu[next] | row | d1 | d2;
	mask = ~mask;
	mask &= (1<<n)-1;
	while(mask){
		int p = mask & (-mask);
		mask ^= p;
		sum += queen(row|p, (d1|p)<<1, (d2|p)>>1, next+1);
	}
    return sum;
}

int BFS(){
	int nSol = 0;
	int pre_l, pre_r, cur_l = 0, cur_r = 1;
	Node *pre_b = node[1], *pre_p, *cur_b = node[0], *cur_p;
	while (cur_r * (n-3) < MAXQ && cur_r != 0){
		pre_l = cur_l, pre_r = cur_r, cur_l = cur_r = 0;
		{ Node *t = pre_b; pre_b = cur_b; cur_b = t; } // Swap
		pre_p = pre_b, cur_p = cur_b;
		while (pre_l < pre_r){
			if (pre_p->next >= n){
				nSol++, pre_l++, pre_p++;
				continue;
			}
			int row = pre_p->row, d1 = pre_p->d1, d2 = pre_p->d2, next = pre_p->next;
			int mask = isOccu[next] | row | d1 | d2;
			mask = ~mask;
			mask &= (1 << n) - 1;
			while (mask){
				int p = mask & (-mask);
				mask ^= p;
				cur_p->row = row | p;
				cur_p->d1 = (d1 | p) << 1;
				cur_p->d2 = (d2 | p) >> 1;
				cur_p->next = next + 1;
				cur_p++, cur_r++;
			}
			pre_l++, pre_p++;
		}
	}

	#pragma omp parallel for schedule(dynamic) reduction(+ : nSol)
	for(int i=cur_l; i<cur_r; i++)
		nSol += queen(cur_b[i].row, cur_b[i].d1, cur_b[i].d2, cur_b[i].next);
	return nSol;
}

int main(){
    while (scanf("%d", &n)==1){
        c++;
		char tmp[32];
        for (int i=0; i<n; i++){
			isOccu[i] = 0;
            scanf("%s", tmp);
			for(int j=0; j<n; j++)
				if(tmp[j]=='*')
					isOccu[i] |= (1<<j);
		}
		node[0][0].next = node[0][0].row = node[0][0].d1 = node[0][0].d2 = 0;
        int nSol = BFS();
        printf("Case %d: %d\n", c, nSol);
    }
    return 0;
}

