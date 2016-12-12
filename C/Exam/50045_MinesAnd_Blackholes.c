#include <stdio.h>
#include <stdlib.h>

#define abs(x) ((x)<0? -1*(x): (x))
#define dist(px, py, pz, qx, qy, qz) (abs(px-qx)+abs(py-qy)+abs(pz-qz))

int main(){
	int x, y, z, mx, my, mz, bx, by, bz;
	scanf("%d %d %d", &x, &y, &z);
	scanf("%d %d %d", &mx, &my, &mz);
	scanf("%d %d %d", &bx, &by, &bz);
	
	int nCase;
	scanf("%d", &nCase);
	int isExplode = 0;
	int isBlack = 0;
	for(int i=1; i<=nCase; i++){
		if(isExplode) continue;
		int step;
		scanf("%d", &step);
		switch(step){
		case 1:
			x+=1; break;
		case 2:
			x-=1; break;
		case 3:
			y+=1; break;
		case 4:
			y-=1; break;
		case 5:
			z+=1; break;
		case 6:
			z-=1; break;
		}
		if(dist(x, y, z, mx, my, mz) < 10){
			x = mx;
			y = my;
			z = mz;
			isExplode = 1;
		}
		else if(!isBlack && dist(x, y, z, bx, by, bz) < 10){
			x = bx;
			y = by;
			z = bz;
			isBlack = 1;
		}

		if(i%5==0 && !isExplode){
			printf("%d %d %d\n", x, y, z);
		}
	}
	return 0;
}
