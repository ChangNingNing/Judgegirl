#include "fill_array.h"

void fill_array(int *ptr[], int n){
	for(int i=0; i<n; i++) *ptr[i] = i;
	for(int *i=ptr[0]+1; i<=ptr[n-1]; i++){
		if(*i<=0) *i = -1;
	}
	int left = *ptr[0];
	for(int *i=ptr[0]+1; i<=ptr[n-1]; i++){
		if(*i<0){
			int j=0;
			while(*(i+j)<0) j++;
			*i = left + *(i+j);
		}
		else{
			left = *i;
		}
	}
}
