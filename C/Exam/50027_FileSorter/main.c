#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Account account[1024];
int nAccount = 0;

int compare(const void *a, const void *b){
	Account *A = (Account *)a, *B = (Account *)b;
	return strcmp(A->name, B->name);
}

int main(){
	char finName[128], foutName[128];
	scanf("%s %s", finName, foutName);
	FILE *fin = fopen(finName, "rb");
	FILE *fout = fopen(foutName, "wb");
	if(!fin || !fout) return 1;
	Account tmp;
	while(fread(&tmp, sizeof(Account), 1, fin)){
		if(tmp.balance < 0) continue;
		if(tmp.gender != 0 && tmp.gender != 1) continue;
		int length = strlen(tmp.name), flag = 0;
		for(int i=0; i<length; i++){
			if(!isalpha(tmp.name[i]) && tmp.name[i]!=' '){
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		
		account[nAccount++] = tmp;
	}
	qsort(account, nAccount, sizeof(account[0]), compare);
	fwrite(account, sizeof(Account), nAccount, fout);
	fclose(fin);
	fclose(fout);
	return 0;
}
