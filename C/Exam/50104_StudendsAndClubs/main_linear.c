#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXK 100001
#define MAXN 5001
#define MAXC 41
typedef struct {
	char lead[MAXC];
	char name[MAXC];
} Club;

typedef struct {
	char club[MAXC];
	char name[MAXC];
} Student;

Club C[MAXN];
Student S[MAXK];
int nC, nS;

int FindClub(char *club){
	for (int i=0; i<nC; i++){
		int ret = strcmp(club, C[i].name);
		if (ret == 0)
			return i;
		else if (ret < 0)
			return -1;
	}
	return -1;
}

int FindStud(char *name, char *club){
	int l = -1, r = nS;
	for (int i=0; i<nS; i++){
		int ret = strcmp(club, S[i].club);
		if (ret < 0){
			r = i;
			break;
		}
		else if (l < 0 && ret == 0){
			l = i;
		}
	}
	if (l < 0) return -1;

	for (int i=l; i<r; i++){
		int ret = strcmp(name, S[i].name);
		if (ret == 0)
			return 1;
		else if (ret < 0)
			return 0;
	}
	return 0;
}

int main(){
	int K;
	scanf("%d", &K);
	for (int i=0; i<K; i++){
		int q;
		char name[MAXC], club[MAXC];
		scanf("%d %s %s", &q, name, club);
		if (q == 0){
			strcpy(C[nC].lead, name);
			strcpy(C[nC].name, club);
			nC++;
		}
		strcpy(S[nS].club, club);
		strcpy(S[nS].name, name);
		nS++;
	}

	int clubComp(const void *a, const void *b){
		Club *A = (Club *)a, *B = (Club *)b;
		return strcmp(A->name, B->name);
	}
	qsort(C, nC, sizeof(Club), clubComp);

	int studentComp(const void *a, const void *b){
		Student *A = (Student *)a, *B = (Student *)b;
		int tmp = strcmp(A->club, B->club);
		if (tmp!=0) return tmp;
		return strcmp(A->name, B->name);
	}
	qsort(S, nS, sizeof(Student), studentComp);

	int Q;
	scanf("%d", &Q);
	for (int i=0; i<Q; i++){
		int q;
		char name[MAXC], club[MAXC];
		scanf("%d", &q);
		if (q == 0){
			scanf("%s", club);
			int ret = FindClub(club);
			if (ret >= 0)
				printf("%s\n", C[ret].lead);
			else
				printf("None\n");
		}
		else {
			scanf("%s %s", name, club);
			printf("%d\n", FindStud(name, club));
		}
	}
	return 0;
}
