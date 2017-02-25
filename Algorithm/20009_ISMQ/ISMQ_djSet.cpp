#include "ISMQ.h"
#include <algorithm>
using namespace std;
 
uint32_t index, r;
uint32_t A[1<<24][3];
uint32_t set[1<<24];
void init_ISMQ(int N) {
    index = r = 0;
}
void append_ISMQ(uint32_t V) {
    A[index][0] = V, A[index][1] = index, A[index][2] = 1;
	uint32_t root = index, *ptr = set+r-1;
	for(int i=r-1; i>=0; i--, ptr--){
		if(A[*ptr][0] < V){
			if(A[*ptr][2] > A[root][2]){
				A[root][1] = *ptr;
				A[*ptr][0] = V;
				root = *ptr;
			}
			else{
				A[*ptr][1] = root;
				A[root][2] += 1;
			}
			r--;
		}
		else break;
	}
	set[r] = root;
    index++, r++;
}
uint32_t FindRoot(uint32_t L){
	if(A[L][1] != L)
		A[L][1] = FindRoot(A[L][1]);
	return A[L][1];
}

uint32_t query_ISMQ(uint32_t L) {
	uint32_t root = FindRoot(L);
	return A[root][0];
}
