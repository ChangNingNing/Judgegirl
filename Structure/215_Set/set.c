#include "set.h"
#include <stdio.h>


typedef unsigned long long Set;
void init(Set *set){
	*set &= 0;
}
void add(Set *set, int i){
	*set |= (unsigned long long)1 << i;
}
void has(Set set, int i){
	if(set & ((unsigned long long)1<<i)) printf("set has %d\n", i);
	else printf("set does not have %d\n", i);
}
Set setUnion(Set a, Set b){
	Set c = a | b;
	return c;
}
Set setIntersect(Set a, Set b){
	Set c = a & b;
	return c;
}
Set setDifference(Set a, Set b){
	Set c = a ^ b;
	return c;
}
