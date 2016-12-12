#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b){
	return strcmp((char *)a, (char *)b);
}

int isSatisfy_1(char x[6]){
	for(int i=0; i<6; i++)
		if(x[i]<'0' || (x[i]>'9' && x[i]<'A') || (x[i]>'Z' && x[i]<'a') || x[i]>'z') return 0;
	return 1;
}

int isSatisfy_2(char x[6]){
	int flag = 0, sum = 0;
	for(int i=0; i<6; i++){
		if(x[i]>='0' && x[i]<='9'){
			flag = 1;
			sum += x[i] - '0';
		}
	}
	if(!flag) return 0;
	if(sum % 7 == 0) return 0;
	return 1;
}

int isSatisfy_3(char x[6]){
	int A[62] = {0};
	for(int i=0; i<6; i++){
		int tmp = -1;
		if(x[i]>='A' && x[i]<='Z') tmp = x[i]-'A';
		else if(x[i]>='a' && x[i]<='z') tmp = x[i]-'a' + 26;
		else tmp = x[i]-'0' + 52;
		if(tmp==-1) continue;
		if(++A[tmp]>2) return 0;
	}
	return 1;
}

int isSatisfy_4(char x[6], int type){
	int flag = 0;
	for(int i=0; i<6; i++){
		if(type == 0 && i==2) flag = 0;
		if(type == 1 && i==3) flag = 0;
		if(x[i]=='4'){
			if(flag) return 0;
			else flag = 1;
		}
		else flag = 0;
	}
}

int main(){
	int N;
	char ans[2][32][8];
	int nAns[2] = {0};
	scanf("%d", &N);
	while(N--){
		char input[8];
		scanf("%s", input);
		char x[6];
		int flag = 0;
		if(input[2]=='-'){
			flag = 0;
			for(int i=0, j=0; i<7; i++, j++){
				if(i!=2) x[j] = input[i];
				else j--;
			}
		}
		else if(input[3]=='-'){
			flag = 1;
			for(int i=0, j=0; i<7; i++, j++){
				if(i!=3) x[j] = input[i];
				else j--;
			}
		}
		else continue;
		
		if(!isSatisfy_1(x)) continue;
		if(!isSatisfy_2(x)) continue;
		if(!isSatisfy_3(x)) continue;
		if(!isSatisfy_4(x, flag)) continue;

		strcpy(ans[flag][nAns[flag]++], input);
	}
	qsort(ans[0], nAns[0], sizeof(ans[0][0]), compare);
	qsort(ans[1], nAns[1], sizeof(ans[1][0]), compare);
	for(int k=0; k<2; k++)
		for(int i=0; i<nAns[k]; i++) puts(ans[k][i]);
	return 0;
}
