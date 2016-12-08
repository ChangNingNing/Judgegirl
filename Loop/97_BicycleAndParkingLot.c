#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ParkingLot[10][4];

int main(){
	int N, M;
	int i, j;
	scanf("%d", &N);
	for(i=0; i<N; i++){
		scanf("%d %d %d", &ParkingLot[i][0], &ParkingLot[i][1], &ParkingLot[i][2]);
		ParkingLot[i][3] = 0;
	}
	scanf("%d", &M);
	for(i=0; i<M; i++){
		int X, Y;
		scanf("%d %d", &X, &Y);
		int min = 30000;
		int minX = 20000;
		int minY = 20000;
		int minP;
		for(j=0; j<N; j++){
			if(ParkingLot[j][2] <= 0) continue;
			else{
				if(abs(ParkingLot[j][0]-X)+abs(ParkingLot[j][1]-Y) < min){
					min = abs(ParkingLot[j][0]-X)+abs(ParkingLot[j][1]-Y);
					minX = ParkingLot[j][0];
					minY = ParkingLot[j][1];
					minP = j;
				}
				else if(abs(ParkingLot[j][0]-X)+abs(ParkingLot[j][1]-Y) == min){
					if(ParkingLot[j][0] < minX){
						minX = ParkingLot[j][0];
						minY = ParkingLot[j][1];
						minP = j;
					}
					else if(ParkingLot[j][0] == minX){
						if(ParkingLot[j][1] < minY){
							minY = ParkingLot[j][1];
							minP = j;
						}
					}
				}
			}
		}
		ParkingLot[minP][2]--;
		ParkingLot[minP][3]++;
	}

	for(i=0; i<N; i++){
		printf("%d\n", ParkingLot[i][3]);
	}
}
