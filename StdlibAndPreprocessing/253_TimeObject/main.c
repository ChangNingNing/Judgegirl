#include "time.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	scanf("%d", &n);
	Time time[n];
	char ins[2];
	while(scanf("%s", ins)!=EOF){
		int index;
		scanf("%d", &index);
		switch(ins[0]){
		case 'i':
			initTime(&time[index]);
			break;
		case 'a':
			;
			int h, m, s;
			scanf("%d %d %d", &h, &m, &s);
			addTime(&time[index], h, m, s);
			break;
		case 's':
			;
			h, m, s;
			scanf("%d %d %d", &h, &m, &s);
			setTime(&time[index], h, m, s);
			break;
		case 'p':
			printTime(&time[index]);
			break;
		}
	}
	return 0;
}
