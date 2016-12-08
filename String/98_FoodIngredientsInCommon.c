#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Food{
	char name[65];
	int num;
	char ingre[10][65];
} Food;

int compare(const void *a, const void *b){
	char *x = (char *)a;
	char *y = (char *)b;
	return strncmp(x, y, 65);
}

int comp(const void *a, const void *b){
	Food *x = (Food *)a;
	Food *y = (Food *)b;
	return strncmp(x->name, y->name, 65);
}

int main(){
	Food food[101];
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%s", food[i].name);
		scanf("%d", &(food[i].num));
		for(int j=0; j<food[i].num; j++) scanf("%s", food[i].ingre[j]);
		qsort(food[i].ingre, food[i].num, sizeof(food[i].ingre[0]), compare);
	}

	qsort(food, n, sizeof(food[0]), comp);
/*
for(int i=0; i<n; i++){
	printf("%s : ", food[i].name);
	for(int j=0; j<food[i].num; j++) printf("%s ", food[i].ingre[j]);
	printf("\n");
}
*/
	int m;
	scanf("%d", &m);
	while(m--){
		char tmp[2][65];
		scanf("%s %s", tmp[0], tmp[1]);
		int tmpI[2];
		for(int i=0; i<n; i++){
			if(strncmp(tmp[0], food[i].name, 65)==0) tmpI[0] = i;
			if(strncmp(tmp[1], food[i].name, 65)==0) tmpI[1] = i;
		}
		int flag = 0;
		int index = 0;
		for(int i=0; i<food[tmpI[0]].num; i++){
			int diff = strncmp(food[tmpI[1]].ingre[index], food[tmpI[0]].ingre[i], 65);
			if(diff < 0){
				index++;
				i--;
			}
			else if(diff==0){
				if(flag) printf(" ");
				printf("%s", food[tmpI[1]].ingre[index]);
				flag = 1;
			}
		}
		if(!flag) printf("nothing");
		printf("\n");
	}
	return 0;
}
