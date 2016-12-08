#include <stdio.h>
#include <stdlib.h>

typedef struct Day {
	int Y, M, D;
} Day;

Day day[1000001];

int compare(const void *a, const void *b){
	Day tmp1 = *(Day *)a;
	Day tmp2 = *(Day *)b;
	if(tmp1.Y != tmp2.Y) return tmp1.Y-tmp2.Y;
	if(tmp1.M != tmp2.M) return tmp1.M-tmp2.M;
	return tmp1.D - tmp2.D;
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d %d %d", &(day[i].Y), &(day[i].M), &(day[i].D));

	qsort((void *)day, n, sizeof(day[0]), compare);

	for(int i=0; i<n; i++)
		printf("%d %d %d\n", day[i].Y, day[i].M, day[i].D);
	return 0;
}
