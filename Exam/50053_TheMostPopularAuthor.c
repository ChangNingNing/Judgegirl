#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Book[101][2];
char *Name[101];
int nName = 0;
int sum[101] = {0};
int max = -1;
int maxP;

int main(){
	int M;
	scanf("%d", &M);
	for(int i=0; i<M; i++){
		char *name = (char *)malloc(sizeof(char)*64);
		char *book = (char *)malloc(sizeof(char)*64);
		scanf("%s %s", name, book);

		int index;
		for(index=0; index<nName && strcmp(Name[index], name); index++){}
		if(index >= nName) Name[nName++] = name;

		Book[i][0] = book;
		Book[i][1] = (char *)index;
	}

	for(int i=0; i<M; i++){
		char book[64];
		int num;
		int index;
		scanf("%s %d", book, &num);

		for(int j=0; j<M; j++){
			if(!strcmp(Book[j][0], book)){
				index = (int)Book[j][1];
				sum[index] += num;
				if(sum[index] > max){
					max = sum[index];
					maxP = index;
				}
				else if(sum[index] == max && strcmp(Name[index], Name[maxP])<0)
						maxP = index;
				break;
			}
		}
	}
	printf("%s %d\n", Name[maxP], max);
	return 0;
}
