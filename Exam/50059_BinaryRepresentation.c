#include <stdio.h>

//unsigned int E[20001] = {0}, N;
int N;
char S[33];
//char A[128001];
//int nA = 0;

int main(){
	scanf("%s", S);
	scanf("%u", &N);
	//for(int i=0; i<N; i++) scanf("%u", &E[i]);

	int index, pre = 0, preN = 0;
	for(int i=0; i<N; i++){
		unsigned int E;
		scanf("%u", &E);
		index = 0;
		while(index < 32){
			if(index + 4 > 31){
				pre = (E << index) >> index;
				preN = 32 - index;
				index += 5;
				continue;
			}
			int preD = pre << (5 - preN);
			int lastIndex = 31 - (index + (4 - preN));
			int decode = preD + ((E >> lastIndex) & 0x1f);
			//A[nA++] = S[decode];
			putchar(S[decode]);
			index += 5 - preN;
			pre = preN = 0;
		}
	}
	puts("");
	//A[nA] = '\0';
	//puts(A);
	return 0;
}
