#include "prepare_array.h"

void prepare_array(int buffer[], int *array[], int row, int column[]){
	int index = 0;
	for(int i=0; i<row; i++){
		array[i] = &(buffer[index]);
		index += column[i];
	}
}
