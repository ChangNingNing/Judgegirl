#include <stdio.h>
#include <stdlib.h>

int main(){
	int countPos, countNeg, length, max, tmp, k;
	scanf("%d", &k);
	countPos = countNeg = length = max = 0;
	while(scanf("%d", &tmp)!=EOF && tmp!=0){
		if(tmp>0){
			countPos++;
			if(countNeg > 0 && countNeg<k) length = 0;
			countNeg = 0;
		}
		else{
			countNeg++;
			if(countPos > 0 && countPos<k) length = 0;
			countPos = 0;
		}
		
		if(countPos > k) length = 1;
		else if(countPos==k && !(length&1)) length++;
		
		if(countNeg > k) length = 0;
		else if(countNeg==k && (length&1)) length++;

		if((length > max) && (length&1) && (length>1)) max = length;
	}
	printf("%d\n", max * k);
	return 0;
}
