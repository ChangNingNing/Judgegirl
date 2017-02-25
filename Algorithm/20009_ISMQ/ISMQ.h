#ifndef _ISMQ_H
#define _ISMQ_H
#include <stdint.h>
 
void init_ISMQ(int N);
void append_ISMQ(uint32_t V);
uint32_t query_ISMQ(uint32_t L);
 
#endif
