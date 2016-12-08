#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct People{
	char name[3][81]; /* 0:lastname; 1:firstname; 2:ID */
	int integer[2]; /* 0:salary; 1:age */
} people;

int main(){
	int nPeople;
	scanf("%d", &nPeople);
	people A[nPeople];
	for(int i=0; i<nPeople; i++){
		for(int j=0; j<3; j++) scanf("%s", A[i].name[j]);
		for(int j=0; j<2; j++) scanf("%d", &A[i].integer[j]);
	}

	int nIns;
	scanf("%d", &nIns);
	while(nIns--){
		char instruction[11][81];
		char condition[3][81];
		int nfield;
		for(nfield=0; ; nfield++){
			scanf("%s", instruction[nfield]);
			if(strncmp(instruction[nfield], "where", 10)==0)
				break;
		}
		if(strncmp(instruction[0], "select", 10)!=0) break;
		for(int i=0; i<3; i++) scanf("%s", condition[i]);

		int condFlag[51] = {0};
		int index = -1;
		switch(condition[0][0]){
		case 's':
			index = 0;
		case 'a':
			index = (index==-1)? 1: index;
			int tmp = atoi(condition[2]);
			for(int i=0; i<nPeople; i++){
				if(condition[1][0]=='='){
					if(tmp==A[i].integer[index]) condFlag[i] = 1;
				}
				else if(condition[1][0]=='>'){
					if(A[i].integer[index]>tmp) condFlag[i] = 1;
				}
				else{
					if(A[i].integer[index]<tmp) condFlag[i] = 1;
				}
			}
			break;
		case 'l':
			index = 0;
		case 'f':
			index = (index==-1)? 1: index;
		case 'I':
			index = (index==-1)? 2: index;
			for(int i=0; i<nPeople; i++){
				if(condition[1][0]=='=' && strncmp(condition[2], A[i].name[index], 81)==0)
					condFlag[i] = 1;
				if(condition[1][0]=='!' && strncmp(condition[2], A[i].name[index], 81)!=0)
					condFlag[i] = 1;
			}
			break;
		}

		for(int i=0; i<nPeople; i++){
			if(!condFlag[i]) continue;
			for(int j=1; j<nfield; j++){
				if(j!=1) printf(" ");
				switch(instruction[j][0]){
				case 's':
					printf("%d", A[i].integer[0]);
					break;
				case 'a':
					printf("%d", A[i].integer[1]);
					break;
				case 'l':
					printf("%s", A[i].name[0]);
					break;
				case 'f':
					printf("%s", A[i].name[1]);
					break;
				case 'I':
					printf("%s", A[i].name[2]);
					break;
				}
				if(j==nfield-1) printf("\n");
			}
		}
	}
	return 0;
}
