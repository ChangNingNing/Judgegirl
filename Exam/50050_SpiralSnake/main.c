#include <stdio.h>
#include "SpiralSnake.h"

#define MAXLEN 1000

int snake[MAXLEN*MAXLEN];
int result[MAXLEN*MAXLEN];

char stk[12];
char buf[1<<20], *ptr = buf;

int readchar() {
#define N 1048576
	    static char buf[N];
		static char *p = buf, *end = buf;
		if(p == end) {
			if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
			p = buf;
		}
		return *p++;
#undef N
}
int ReadInt(int *x) {
		static char c, neg;
		while((c = readchar()) < '-')    {if(c == EOF) return 0;}
		neg = (c == '-') ? -1 : 1;
		*x = (neg == 1) ? c-'0' : 0;
		while((c = readchar()) >= '0')
				*x = (*x << 3) + (*x << 1) + c-'0';
		*x *= neg;
		return 1;
}

void myPrint(int x, char end){
		int nstk = 0;
		stk[nstk++] = end;
		if(!x) stk[nstk++] = '0';
		while(x){
				stk[nstk++] = (x % 10) + '0', x /= 10;
		}
		while(nstk){
				if(buf + (1<<20) - ptr < 1<<4){
						*ptr = '\0';
						printf("%s", buf), ptr = buf;
				}
				*ptr = stk[--nstk], ptr++;
		}
		return;
}

void endPrint(){
		*ptr = '\0';
		printf("%s", buf), ptr = buf;
}

int main(){
		int N;
		//while(scanf("%d", &N)!=EOF){
		while(ReadInt(&N)==1){	
			for(int i=0; i<N*N; i++){
					//if(scanf("%d", &snake[i])){};
					ReadInt(&snake[i]);
				}
				SpiralSnake(N, snake, result);
				for(int i=0; i<N*N; i++){
						//printf("%d%c", newSnake[i], " \n"[i==N*N-1]);
						myPrint(result[i], i==N*N-1? '\n': ' ');
				}
				endPrint();
		}
		return 0;
}
