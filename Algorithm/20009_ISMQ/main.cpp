#include <bits/stdc++.h>
#include "ISMQ.h"
 
using namespace std;
 
static uint32_t seed = 0;
static uint32_t p_func(uint32_t x) {return x*9301+49297;}
static uint32_t p_random() {return seed = p_func(seed);}
 
// #define _DEBUG
int main() {
    int N, M, S, MOD;
    assert(scanf("%d %d %d %d", &N, &M, &S, &MOD) == 4);
 
    seed = S;
 
    uint32_t hash = 0;
#ifdef _DEBUG
    static int D[1048576];
#endif
    for (int it = 0; it < M; it++) {
        init_ISMQ(N);
        for (int i = 0; i < N; i++) {
            // step 1: append value to array $A$
            {
                uint32_t V = p_random()%MOD;
                append_ISMQ(V);
#ifdef _DEBUG
                D[i] = V;
#endif
            }
            // step 2: query suffix maximum in $A\lbrack L, i]$
            {
                int L = p_random()%(i+1);
                uint32_t ans = query_ISMQ(L);
                hash ^= ans;
#ifdef _DEBUG
                printf("max(A[%2d, %2d]) = %u\n", L, i, ans);
#endif
            }
        }
    }
 
#ifdef _DEBUG
    printf("[");
    for (int i = 0; i < N; i++)
        printf("%2u%c", D[i], i == N-1 ? ']' : ' ');
    puts("");
#endif
 
    printf("%X\n", hash);
    return 0;
}
