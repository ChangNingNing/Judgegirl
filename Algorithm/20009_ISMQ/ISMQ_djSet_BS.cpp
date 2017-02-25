#include "ISMQ.h"
#include <algorithm>
using namespace std;
 
int index, R;
uint32_t A[1<<24];
uint32_t set[1<<24];
void init_ISMQ(int N) {
    index = R = 0;
}
void append_ISMQ(uint32_t V) {
    A[index] = V;
	for(int i=R-1; i>=0; i--){
		if(A[set[i]] < V) R--;
		else break;
	}
	set[R] = index;
    index++, R++;
}

uint32_t BS(uint32_t key, int l, int r){
	uint32_t mid, pos;
	while(l <= r){
		mid = (l+r)/2, pos = set[mid];
		if(pos > key) r = mid - 1;
		else if(pos < key) l = mid + 1;
		else return pos;
	}
	return set[l];
}

uint32_t query_ISMQ(uint32_t key){
	return A[BS(key, 0, R-1)];
}
