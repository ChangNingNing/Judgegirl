#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
#define MAXN 20
 
int N;
char Word[MAXN][64];
int Cost[MAXN] = {0}, Bit[MAXN] = {0}, isUse[MAXN] = {0};
float UnitCost[MAXN];
int Bound = 0, answer = 0x03ffffff;
 
void WordSelection(int index, int cost, int bit, int use[]){
    if(cost >= Bound) return;
    if(bit >= answer && cost < Bound){
        Bound = cost;
        for(int i=0; i<N; i++) isUse[i] = use[i];
    }
    if(index >= N) return;
 
    use[index] = 1;
    cost += Cost[index];
    int tmpBit = bit | Bit[index];
    WordSelection(index+1, cost, tmpBit, use);
    use[index] = 0;
    cost -= Cost[index];
    WordSelection(index+1, cost, bit, use);
    return;
}
 
int main(){
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%s %d", Word[i], &Cost[i]);
        int length = strlen(Word[i]);
        for(int j=0; j<length; j++)
            Bit[i] |= (1 << (Word[i][j]-'a'));
        int tmp = 0;
        for(int j=0; j<26; j++)
            if((Bit[i]>>j) & 1) tmp++;
        if(tmp) UnitCost[i] = (float)Cost[i] / tmp;
        else UnitCost[i] = -1;
    }
 
    //Greedy
    int tmp = 0;
    while(tmp < answer){
        float min = INT_MAX;
        int minP = -1;
        for(int i=0; i<N; i++)
            if(isUse[i]==0 && UnitCost[i] < min) min = UnitCost[i], minP = i;
        isUse[minP] = 1;
        tmp |= Bit[minP];
        Bound += Cost[minP];
    }
 
    // Recursion
    int tmpUse[MAXN] = {0};
    WordSelection(0, 0, 0, tmpUse);
 
    printf("%d\n", Bound);
    return 0;
}
