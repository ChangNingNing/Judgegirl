#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	scanf("%d", &n);
	/* downhill=0; uphill=1 */
	int hill = 0;
	int previous, current;
	int sum = 0;
	scanf("%d", &previous);
	for(int i=1; i<n; i++){
		scanf("%d", &current);
		if(current-previous > 0){
			if(hill==0)
				sum += (current-previous)*3;
			else
				sum += (current-previous)*4;
			hill = 1;
		}
		else{
			if(hill==0)
				sum += (previous-current)*2;
			else
				sum += (previous-current)*3;
			hill = 0;
		}
		previous = current;
	}
	printf("%d\n", sum);
	return 0;
}
