#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char subset[200000][502];
int n = 0;

int compare(const void *a, const void *b){
	char *x = (char *)a;
	char *y = (char *)b;
	return strncmp(x, y, 500);
}

int main(){
	char input[502];
	scanf("%s", input);
	int length = strlen(input);
	for(int i=length; i>0; i--){
		for(int j=0; j<length && j+i<=length; j++){
			strncpy(subset[n], input+j, i);
			n++;
		}
	}
	qsort(subset, n, sizeof(subset[0]), compare);
	for(int i=0; i<n; i++){
		if(i!=0 && strncmp(subset[i], subset[i-1], 500)==0) continue;
		puts(subset[i]);
	}
	return 0;
}
