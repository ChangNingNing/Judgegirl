#include <stdio.h>
#include <stdlib.h>
#define dist(x1, y1, x2, y2) (((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))

int City[100000][3] = {0};
int nCity = 0;

int compare(const void *a, const void *b){
	int distA = *(int *)(a + 2*sizeof(int));
	int distB = *(int *)(b + 2*sizeof(int));
	if(distA != distB) return distA - distB;
	
	int xA = *(int *)a;
	int xB = *(int *)b;
	if(xA != xB) return xA - xB;

	int yA = *(int *)(a + sizeof(int));
	int yB = *(int *)(b + sizeof(int));
	return yA - yB;
}

int main(){
	while(scanf("%d %d", &City[nCity][0], &City[nCity][1])!=EOF){
		City[nCity][2] = dist(City[nCity][0], City[nCity][1], 0, 0);
		nCity++;
	}
	qsort((void *)City, nCity, sizeof(City[0]), compare);
	int sum = 0;
	int tmpX = 0, tmpY = 0;
	
	for(int i=0; i<nCity; i++){
		sum += dist(tmpX, tmpY, City[i][0], City[i][1]);
		tmpX = City[i][0];
		tmpY = City[i][1];
	}
	printf("%d\n", sum);
	return 0;
}
