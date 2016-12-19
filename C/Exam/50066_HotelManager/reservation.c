#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>

int isValid(RoomStatus *room, int nP, int sT, int eT){
	Reservation *pre = NULL, *cur = room->reservation;
	for(; cur!=NULL; pre=cur, cur=cur->next){
		if(eT <= cur->StartTime) break;
		if(sT < cur->EndTime) return 0;
	}
	Reservation *tmp = (Reservation *)malloc(sizeof(Reservation));
	tmp->nP = nP, tmp->StartTime = sT, tmp->EndTime = eT;
	if(pre == NULL)
		room->reservation = tmp;
	else
		pre->next = tmp;
	tmp->next = cur;
	return 1;
}

int ReserveRoom(RoomStatus list[], int n, int nP, int StartTime, int EndTime){
	for(int i=0; i<n; i++){
		if(list[i].capacity >= nP){
			if(isValid(&list[i], nP, StartTime, EndTime))
				return 1;
		}
	}
	return 0;
}
