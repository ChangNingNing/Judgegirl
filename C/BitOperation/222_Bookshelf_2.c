#include <stdio.h>
#include <stdlib.h>

int hasEOF = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;   
        }
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

int main(){
	long long int answer = 0;
	int book;
	while(ReadInt(&book)){
		int i;
		for(i=0; i<64; i+=8){
			if(((answer>>i)&0xff) == book){
				answer ^= ((long long)book << i);
				long long int temp1 = (answer >> i) << i;
				long long int temp2 = answer ^ temp1;
				answer ^= temp2;
				answer += temp2<<8;
				answer += book;
				break;
			}
		}
		if(i==64){
			answer = answer << 8;
			answer += book;
		}
	}
	for(int i=56; i>=0; i=i-8){
		printf("%d", (answer>>i)&0xff);
		if(i!=0) printf(" ");
	}
	printf("\n");
	return 0;
}
