#include "book.h"
#include "date.h"

int MonthDay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int period[4] = {90, 10, 100, 5};

int countDay(struct Date date){
	int diffY = date.year - 1000;
	int sum = diffY * 365;
	sum += (date.year-1)/4-(date.year-1)/100+(date.year-1)/400 - 242;
	if(date.year%4==0 && date.year%100!=0 || date.year%400==0) MonthDay[1] = 29;
	for(int i=0; i<date.month-1; i++) sum += MonthDay[i];
	sum += date.day - 1;
	MonthDay[1] = 28;
	return sum;
}

unsigned int library_fine(struct Book book, struct Date date_borrowed, struct Date date_returned){
	int borrowedDay = countDay(date_returned) - countDay(date_borrowed) + 1;
	int overdue = borrowedDay - period[book.type];
	if(overdue <= 0) return 0;
	
	int index[2];
	int j=0;
	for(int i=0; i<32; i++){
		if((book.importance >> i) & 1) index[j++] = i;
		if(j>1) break;
	}
	int importance = index[1] - index[0] - 1;
	return importance * overdue;
}
