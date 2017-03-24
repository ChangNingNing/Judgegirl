#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
int V[512], accV[512] = {0}, DP[512]={0};
 
int main(){
    int N, M;
    while (scanf("%d %d", &N, &M)==2){
        for (int i=1; i<=N; i++){
            scanf("%d", &V[i]);
            accV[i] = accV[i-1] + V[i];
            DP[i] = V[i]*i - accV[i];
        }
        for(int i=2; i<=M; i++){
            for(int j=N-M+i; j>=i; j--){
                int min = INT_MAX, mid = j-1;
                for(int k=j-1; k>=i-1; k--){
                    while(V[j]-V[mid] <= V[mid]-V[k]) mid--;
                    int lcost = accV[mid]-accV[k]-V[k]*(mid-k);
                    int rcost = V[j]*(j-mid)-(accV[j]-accV[mid]);
                    int tmp = DP[k] + lcost + rcost;
                    if(tmp < min) min = tmp;
                }
                DP[j] = min;
            }
        }
        int min = INT_MAX;
        for(int i=M; i<=N; i++){
            int tmp = DP[i] + accV[N]-accV[i]-V[i]*(N-i);
            if(tmp < min) min = tmp;
        }
        printf("%d\n", min);
    }
    return 0;
}
