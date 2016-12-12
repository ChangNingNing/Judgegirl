#include "time.h"
#include <stdio.h>
#include <stdlib.h>

void initTime(Time *time){
	time->hour = time->minute = time->second = 0;
	return;
}
void setTime(Time *time, int hour, int minute, int second){
	time->hour = hour;
	time->minute = minute;
	time->second = second;
	return;
}
void addTime(Time *time, int hour, int minute, int second){
	int sum = hour*3600 + minute*60 + second;
	time->second += sum;
	time->minute += time->second/60;
	time->second %= 60;
	time->hour += time->minute/60;
	time->minute %= 60;
	time->hour %= 24;
	return;
}
void printTime(Time *time){
	#ifdef H24
	printf("%02d:%02d:%02d\n", time->hour, time->minute, time->second);
	return;
	#endif
	
	if(time->hour > 12) printf("%02dpm:", time->hour-12);
	else if(time->hour == 12) printf("%02dpm:", time->hour);
	else if(time->hour == 0) printf("%02dam:", time->hour+12);
	else printf("%02dam:", time->hour);
	printf("%02d:%02d\n", time->minute, time->second);
	return;
}
