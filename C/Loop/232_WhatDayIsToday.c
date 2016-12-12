#include <stdio.h>
#include <stdlib.h>

int table[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int accTable[12];

int main(){
	int year, day;
	int nCase;
	int i;
	scanf("%d %d", &year, &day);
	scanf("%d", &nCase);
	if((year%4==0 && year%100!=0) || year%400==0)
		table[1] = 29;
	accTable[0] = 31;
	for(i=1; i<12; i++){
		accTable[i] = accTable[i-1] + table[i];
	}
	while(nCase--){
		int month, date;
		scanf("%d %d", &month, &date);
		if(month>12 || month<1){
			printf("-1\n");
			continue;
		}
		if(date > table[month-1] || date < 1){
			printf("-2\n");
			continue;
		}
		int tmp = (month>1)? accTable[month-2] + date - 1: date - 1;
		int newDay = (tmp + day) % 7;
		printf("%d\n", newDay);
	}
	return 0;
}
