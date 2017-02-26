#include "ISMQ.h"
#include <algorithm>
using namespace std;
 
uint32_t index, nSet;
uint32_t Value[1<<24], Parent[1<<24];
uint32_t Rank[1<<24], Set[1<<24];
void init_ISMQ(int N) {
    index = nSet = 0;
}
void append_ISMQ(uint32_t V) {
    Value[index] = V, Parent[index] = index;
    uint32_t root = index, *ptr = Set+nSet-1, tmpRank = 1;
    for (int i=nSet-1; i>=0; i--, nSet--, ptr--){
        if (Value[*ptr] <= V){
            if (Rank[i] >= tmpRank){
                Parent[root] = *ptr;
                root = *ptr;
                tmpRank = Rank[i];
            }
            else {
                Parent[*ptr] = root;
                tmpRank += 1;
            }
        }
        else break;
    }
    Set[nSet] = root;
    Rank[nSet] = tmpRank;
	Value[Set[nSet]] = V;
    index++, nSet++;
}
uint32_t FindRoot(uint32_t L){
    if (Parent[L] != L)
        Parent[L] = FindRoot(Parent[L]);
    return Parent[L];
}
 
uint32_t query_ISMQ(uint32_t L) {
    return Value[FindRoot(L)];
}
