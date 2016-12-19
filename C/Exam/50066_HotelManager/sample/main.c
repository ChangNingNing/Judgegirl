#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int n = 3;
	RoomStatus list[n];
	for(int i=0; i < n; i++){
		list[i].capacity = i+2;
		list[i].reservation = NULL;
	}
	int nP, sTime, eTime;
	while(scanf("%d %d %d", &nP, &sTime, &eTime)!=EOF)
		printf("%d", ReserveRoom(list, n, nP, sTime, eTime));
	puts("");
	printf("---Room Status List---\n");
	for(int i=0; i<n; i++){
		printf("%d ---", list[i].capacity);
		for(Reservation *tmp = list[i].reservation; tmp!=NULL; tmp=tmp->next)
			printf("->(%d:%d, %d)", tmp->nP, tmp->StartTime, tmp->EndTime);
		puts("");
	}
	printf("---      End       ---\n");
	return 0;
}
