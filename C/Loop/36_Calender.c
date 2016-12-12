#include <stdio.h>
#include <stdlib.h>

int nOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main(){
	int year, month, day;
	int i;
	scanf("%d %d %d", &year, &month, &day);

	if(month > 12 || month < 1 || day > 6 || day < 0){
		printf("invalid\n");
	}
	else{
		if((year%4==0 && year%100!=0) || year%400==0)
			nOfMonth[1] = 29;
		printf(" Su Mo Tu We Th Fr Sa\n");
		printf("=====================\n");
		int j = day;
		for(i=0; i<day; i++)
			printf("   ");
		for(i=1; i<=nOfMonth[month-1]; i++){
			printf("%3d", i);
			j++;
			if(j==7){
				printf("\n");
				j %= 7;
			}
		}
		if(j) printf("\n");
		printf("=====================\n");
	}
	return 0;
}