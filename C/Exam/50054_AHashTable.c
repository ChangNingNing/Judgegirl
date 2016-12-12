#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct myS{
	int key;
	char value[101];
} myS;

int S, N, Q;
myS table[10000];
int nTable = 0;

int compare(const void *a, const void *b){
	myS *A = (myS *)a;
	myS *B = (myS *)b;
	if(A->key != B->key) return A->key - B->key;
	return strcmp(A->value, B->value);
}

int Hash(char *s){
	int length = strlen(s), sum = 0;
	for(int i=0; i<length; i++){
		if(s[i]<='9' && s[i]>='0') sum += s[i] - '0';
		else sum += s[i];
	}
	return sum;
}

int BS(int key, char *value, int l, int r){
	if(l > r) return -1;
	int m = (l+r)/2;
	if(table[m].key == key){
		int tmp = strcmp(table[m].value, value);
		if(!tmp) return m;
		else if(tmp > 0) return BS(key, value, l, m-1);
		else return BS(key, value, m+1, r);
	}
	else{
		if(table[m].key > key) return BS(key, value, l, m-1);
		else return BS(key, value, m+1, r);
	}
}

int main(){
	scanf("%d %d %d", &S, &N, &Q);
	for(int i=0; i<N; i++){
		scanf("%s", table[nTable].value);
		table[nTable].key = Hash(table[nTable].value);
		nTable++;
	}
	qsort(table, nTable, sizeof(table[0]), compare);
/*
for(int i=0; i<nTable; i++){
	printf("%d %s\n", table[i].key, table[i].value);
}
*/
	for(int i=0; i<Q; i++){
		char query[101];
		scanf("%s", query);
		int index = BS(Hash(query), query, 0, nTable-1);
		if(index == -1) printf("-1\n");
		else printf("%d\n", table[index].key % S);
	}
	return 0;
}
