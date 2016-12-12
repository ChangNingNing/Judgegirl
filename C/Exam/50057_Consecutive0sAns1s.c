#include <stdio.h>

void myPrint(char digit, int count, int space){
	for(int i=0; i<space; i++) putchar(' ');
	for(int i=0; i<count; i++) putchar(digit);
	puts("");
	return;
}

int main(){
	int N, pre = 0, count = 0, space = 0;
	for(scanf("%d", &N)==1; N; N--){
		unsigned int tmp;
		scanf("%u", &tmp);
		for(int i=31; i>=0; i--){
			int digit = (tmp >> i) & 1;
			if(!(pre ^ digit)) count++;
			else{
				myPrint(pre + '0', count, space);
				space = (space + count) % 40;
				count = 1;
				pre = digit;
			}
		}
	}
	myPrint(pre + '0', count, space);
	return 0;
}
