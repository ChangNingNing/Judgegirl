#include "ISMQ.h"
#include <assert.h>
#include <algorithm>
using namespace std;
 
int index, nSet;
uint32_t Set[1<<24];
uint32_t Range[1<<24];
void init_ISMQ(int N) {
    index = nSet = 0;
}
void append_ISMQ(uint32_t V) {
	int l = index;
	for(int i=nSet-1; i>=0; i--){
		if(Set[i] < V){
			l = Range[i];
			nSet--;
		}
		else break;
	}
	Set[nSet] = V, Range[nSet] = l;
    index++, nSet++;
}

uint32_t BS(uint32_t key, uint32_t l, uint32_t r){
	uint32_t mid, pos;
	while(l <= r){
		mid = (l+r)/2, pos = Range[mid];
		if(pos > key) r = mid - 1;
		else if(pos < key) l = mid + 1;
		else return mid;
	}
	return r;
}

uint32_t query_ISMQ(uint32_t key){
	return Set[BS(key, 0, nSet-1)];
}
