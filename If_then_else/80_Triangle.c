#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int num;
	int i;
	scanf("%d", &num);
	while(num--){
		int x[8];
		int a2[3];
		for(i=0; i<6; i++)
			scanf("%d", &x[i]);
		x[6] = x[0];
		x[7] = x[1];
		int maxP;
		int max = 0;
		for(i=0; i<6; i+=2){
			a2[i/2] = pow(x[i]-x[i+2],2) + pow(x[i+1]-x[i+3],2);
			if(a2[i/2] > max){
				maxP = i/2;
				max = a2[i/2];
			}
		}
		if(a2[0]==a2[1] || a2[0]==a2[2] || a2[1]==a2[2])
			printf("isosceles\n");
		else{
			if(a2[maxP] == a2[(maxP+1)%3] + a2[(maxP+2)%3])
				printf("right\n");
			else if(a2[maxP] > a2[(maxP+1)%3] + a2[(maxP+2)%3])
				printf("obtuse\n");
			else
				printf("acute\n");
		}
	}
	return 0;
}
