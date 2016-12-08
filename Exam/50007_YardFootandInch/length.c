#include "length.h"
#include <stdio.h>

void init(int length[3]) {
	length[0] = length[1] = length[2] = 0;
	return;
}
void add(int length[3], int i) {
	length[2] += i;
	if(length[2]<12) return;
	length[1] += length[2]/12;
	length[2] %= 12;
	if(length[1]<3) return;
	length[0] += length[1]/3;
	length[1] %= 3;
	return;
}
void sum(int lengtha[3], int lengthb[3], int lengthc[3]) {
	for(int i=0; i<3; i++) lengthc[i] = lengtha[i] + lengthb[i];
	add(lengthc, 0);
	return;
}
void diff(int lengtha[3], int lengthb[3], int lengthc[3]) {
	lengtha[1] += lengtha[0] * 3;
	lengtha[2] += lengtha[1] * 12;
	lengthb[1] += lengthb[0] * 3;
	lengthb[2] += lengthb[1] * 12;
	
	init(lengthc);
	lengthc[2] = lengtha[2] - lengthb[2];
	add(lengthc, 0);
	return;
}
