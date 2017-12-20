#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXK 100001
#define MAXN 5001
#define MAXC 41

typedef struct {
	char club[MAXC];
	char name[MAXC];
	int isLead;
} Student;

Student S[MAXK];
int nS;

int FindStud(char *name, char *club){
	int l = 0, r = nS - 1;
	while (l <= r){
		int mid = (l + r) >> 1;
		int ret = strcmp(club, S[mid].club);
		if (ret <= 0) r = mid - 1;
		else l = mid + 1;
	}
	if (strcmp(club, S[l].club) != 0)
		return -1;
	if (name == NULL)
		return l;
	if (strcmp(name, S[l].name) == 0)
		return 1;

	l = l + 1, r = nS - 1;
	while (l <= r){
		int mid = (l + r) >> 1;
		int ret = strcmp(club, S[mid].club);
		if (ret == 0){
			int ret2 = strcmp(name, S[mid].name);
			if (ret2 == 0) return 1;
			else if (ret2 < 0) r = mid - 1;
			else l = mid + 1;
		}
		else if (ret < 0) r = mid - 1;
		else l = mid + 1;
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
		strcpy(S[nS].club, club);
		strcpy(S[nS].name, name);
		S[nS].isLead = q==0? 1: 0;
		nS++;
	}

	int comp(const void *a, const void *b){
		Student *A = (Student *)a, *B = (Student *)b;
		int tmp = strcmp(A->club, B->club);
		if (tmp!=0) return tmp;
		else if (A->isLead != B->isLead) return -(A->isLead - B->isLead);
		return strcmp(A->name, B->name);
	}
	qsort(S, nS, sizeof(Student), comp);

	int Q;
	scanf("%d", &Q);
	for (int i=0; i<Q; i++){
		int q;
		char name[MAXC], club[MAXC];
		scanf("%d", &q);
		if (q == 0){
			scanf("%s", club);
			int ret = FindStud(NULL, club);
			if (ret >= 0)
				printf("%s\n", S[ret].name);
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
