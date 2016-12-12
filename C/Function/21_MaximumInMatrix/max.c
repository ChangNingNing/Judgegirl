#include "max.h"

int max(int array[5][5]){
	int T = -100000;
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(array[i][j]>T) T = array[i][j];
		}
	}
	return T;
}
