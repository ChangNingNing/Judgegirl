#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prize[6] = {200000, 40000, 10000, 4000, 1000, 200};

int main(){
	char special[3][9], first[3][9];
	int i, j;
	for(i=0; i<3; i++)
		scanf("%s", special[i]);
	for(i=0; i<3; i++)
		scanf("%s", first[i]);
	char lottery[9];
	int sum = 0;
	while(scanf("%s", lottery) != EOF){
		int flag = 0;
		for(i=0; i<3; i++){
			if(strncmp(lottery, special[i], 8)==0){
				sum += 2000000;
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		for(i=0; i<6; i++){
			for(j=0; j<3; j++){
				if(strncmp(lottery+i, first[j]+i, 8-i)==0){
					sum += prize[i];
					flag = 1;
					break;
				}
			}
			if(flag) break;
		}
		if(flag) continue;
	}
	printf("%d\n", sum);
	return 0;
}
