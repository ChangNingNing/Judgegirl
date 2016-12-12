#include "intersection.h"

void intersection(int map[100][100], int result[4]){
	int intersection = 0, T_junction = 0, turn = 0, dead_end = 0;
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			if(map[i][j]){
				int tmp = 0;
				if(map[i-1][j] && i-1>=0) tmp++;
				if(map[i+1][j] && i+1<100) tmp++;
				if(map[i][j-1] && j-1>=0) tmp++;
				if(map[i][j+1] && j+1<100) tmp++;
				if(tmp==4) intersection++;
				else if(tmp==3) T_junction++;
				else if(tmp==2 && (!map[i-1][j] || i-1<0 || !map[i+1][j] || i+1>=100) && (!map[i][j-1] || j-1<0 || !map[i][j+1] || j+1>=100)) turn++;
				else if(tmp==1) dead_end++;
			}
		}
	}
	result[0] = intersection;
	result[1] = T_junction;
	result[2] = turn;
	result[3] = dead_end;
}
