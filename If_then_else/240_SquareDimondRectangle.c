#include <stdio.h>
#include <stdlib.h>

#define pow(a, b, c, d) (((a)-(c))*((a)-(c))+((b)-(d))*((b)-(d)))

int main(){
	int num;
	int i;
	scanf("%d", &num);
	while(num--){
		int x[8];
		int edge[6];
		for(i=0; i<8; i+=2)
			scanf("%d %d", &x[i], &x[i+1]);
		for(i=2; i<8; i+=2){
			int v[4];
			v[0] = x[i]-x[i-2];
			v[1] = x[i+1]-x[i-1];
			v[2] = x[(i+2)%8]-x[i];
			v[3] = x[(i+3)%8]-x[i+1];
			if(v[0]*v[3] - v[1]*v[2] < 0){
				int tempX = x[i], tempY = x[i+1];
				x[i] = x[(i+2)%8];
				x[i+1] = x[(i+3)%8];
				x[(i+2)%8] = tempX;
				x[(i+3)%8] = tempY;
			}
		}
		edge[0] = pow(x[0], x[1], x[2], x[3]);
		edge[1] = pow(x[2], x[3], x[4], x[5]);
		edge[2] = pow(x[4], x[5], x[6], x[7]);
		edge[3] = pow(x[6], x[7], x[0], x[1]);
		edge[4] = pow(x[0], x[1], x[4], x[5]);
		edge[5] = pow(x[2], x[3], x[6], x[7]);
		if(edge[0]==edge[1] && edge[0]==edge[2] && edge[0]==edge[3]){
			if(edge[4]==edge[5])	printf("square\n");
			else printf("diamond\n");
		}
		else if(edge[0]==edge[2] && edge[1]==edge[3]){
			if(edge[4]==edge[5]) printf("rectangle\n");
			else printf("other\n");
		}
		else printf("other\n");
	}
	return 0;
}
