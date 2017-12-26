#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define MAXC 64

typedef struct {
	char name[MAXC];
	int h, w;
	float b;
} Student;
Student S[MAXN];

int main(){
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		scanf("%s %d %d", S[i].name, &S[i].h, &S[i].w);
		S[i].b = (float) S[i].w / S[i].h / S[i].h;
	}

	{
		int comp(const void *a, const void *b){
			Student *A = (Student *)a, *B = (Student *)b;
			if (A->b != B->b) return A->b - B->b > 0? 1: -1;
			if (A->w != B->w) return A->w - B->w;
			if (A->h != B->h) return A->h - B->h;
			return strcmp(A->name, B->name);
		}
		qsort(S, N, sizeof(Student), comp);
	}

	for (int i=0; i<N; i++)
		printf("%s %d %d\n", S[i].name, S[i].h, S[i].w);
	return 0;
}
