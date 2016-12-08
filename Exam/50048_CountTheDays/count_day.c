#include "count_day.h"
#include <stdio.h>
#include <stdlib.h>


void count_day(int year, int day, int month, int results[7]){
	int num[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(year % 400==0 || (year%4==0 && year%100!=0)) num[1] = 29;
	int sum = 0;
	for(int i=0; i<month-1; i++) sum += num[i];
	day = (day + sum % 7) % 7;
	int r = num[month-1]%7;
	int q = num[month-1]/7;
	for(int i=0; i<7; i++) results[i] = q;
	for(int i=day; i<7 && r>0; i = (i+1)%7, r--) results[i]++;
	return;
}
