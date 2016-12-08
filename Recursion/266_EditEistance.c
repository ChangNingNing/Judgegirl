#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int min = INT_MAX;

int MIN(int x, int y){
	return (x<y)? x: y;
}

int compare(char *x, char *y, int Nx, int Ny, int dist){
	if(dist > min) return dist;
	if(Nx==0 || Ny==0) return dist+Nx+Ny;
	if(x[0]==y[0])
		return compare(x+1, y+1, Nx-1, Ny-1, dist);
	else
		return MIN(compare(x+1, y, Nx-1, Ny, dist+1), compare(x, y+1, Nx, Ny-1, dist+1));
}

int main(){
	char input[101][11];
	int num = 0;
	int minValue = INT_MAX;
	int minP1, minP2;
	while(scanf("%s", input[num])!=EOF) num++;
	for(int i=0; i<num; i++){
		for(int j=i+1; j<num; j++){
			int dist = compare(input[i], input[j], strlen(input[i]), strlen(input[j]), 0);
			if(dist<min || dist == min && (i+1)*1000+(j+1)<minValue){
				min = dist;
				minP1 = i+1;
				minP2 = j+1;
				minValue = minP1*1000+minP2;
			}
		}
	}
	printf("%d %d %d\n", min, minP1, minP2);
	return 0;
}
