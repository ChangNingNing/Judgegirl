#include "ISMQ.h"
#include <algorithm>
using namespace std;
 
int index;
uint32_t A[1<<24];
void init_ISMQ(int N) {
    index = 0;
}
void append_ISMQ(uint32_t V) {
    A[index] = V;
	for(int i=index-1; A[i]<V && i>=0; i--)
		A[i] = V;
    index++;
}
uint32_t query_ISMQ(uint32_t L) {
	return A[L];
}
