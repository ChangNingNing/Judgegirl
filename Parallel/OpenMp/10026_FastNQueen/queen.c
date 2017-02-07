#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <assert.h>
#define MAXN 20

int isOccu[MAXN];

int queen(int row, int d1, int d2, int next, int n){
    if(next >= n) return 1;
    int sum = 0;
    int mask = isOccu[next] | row | d1 | d2;
    mask = ~mask;
    mask &= (1<<n)-1;
    while(mask){
        int p = mask & (-mask);
        mask ^= p;
        sum += queen(row|p, (d1|p)<<1, (d2|p)>>1, next+1, n);
    }
    return sum;
}

int main(){
    int n, c = 0;
    while(scanf("%d", &n)==1){
        c++;
        char tmp[32];
        for(int i=0; i<n; i++){
            isOccu[i] = 0;
            scanf("%s", tmp);
            for(int j=0; j<n; j++)
                if(tmp[j]=='*')
                    isOccu[i] |= (1<<j);
        }
        int nSol = 0;
        #pragma omp parallel for schedule(static, 1) reduction(+ : nSol)
        for(int i=0; i<n; i++){
            if(!((isOccu[0]>>i) & 1)){
                int pos[MAXN];
                int row=0, d1=0, d2=0;
                pos[0] = i;
                d1 = d2 = row |= (1<<i);
                nSol += queen(row, d1<<1, d2>>1, 1, n);
            }
        }
        printf("Case %d: %d\n", c, nSol);
    }
    return 0;
}

