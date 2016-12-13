#include "car.h"
#include <stdio.h>

CarStatusList carSimulation(CarStatus car, Command commands[]){
	CarStatusList list;
	int flag = 1, n = 0;
	list.num = 0;
	while(flag){
		switch(commands[n].t){
		case 0:
			flag = 0;
			break;
		case 1:
			car.g += commands[n].v;
			break;
		case 2:
			if(commands[n].v > car.g) flag = 0;
			else{
				car.x += commands[n].v;
				car.g -= commands[n].v;
			}
			break;
		case 3:
			if(commands[n].v > car.g) flag = 0;
			else{
				car.x -= commands[n].v;
				car.g -= commands[n].v;
			}
			break;
		case 4:
			if(commands[n].v > car.g) flag = 0;
			else{
				car.y += commands[n].v;
				car.g -= commands[n].v;
			}
			break;
		case 5:
			if(commands[n].v > car.g) flag = 0;
			else{
				car.y -= commands[n].v;
				car.g -= commands[n].v;
			}
			break;
		}
		if(flag && commands[n].t != 1){
			list.status[list.num].x = car.x;
			list.status[list.num].y = car.y;
			list.status[list.num].g = car.g;
			list.num++;
		}
		n++;
	}
	return list;
}
