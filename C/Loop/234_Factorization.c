#include <stdio.h>
#include <stdlib.h>

long long int a, b, c;
long long int F(long long int x){
	long long int answer;
	answer = x*x*x + a*x*x + b*x + c;
	return answer;
}

long long int FF(long long int x){
	long long int answer;
	answer = 3*x*x + 2*a*x + b;
	return answer;
}

int main(){
	scanf("%lld %lld %lld", &a, &b, &c);
	int i;
	int root[3];
	int N = 0;
	for(i=-100000; i<100001; i++){
		if(F(i) == 0){
			root[N] = -1*i;
			N++;
			if(N==3) break;
		}
	}
	switch(N){
	case 1:
		root[1] = root[2] = root[0];
		break;
	case 2:
		if(FF(-1*root[0]) == 0){
			root[2] = root[1];
			root[1] = root[0];
			break;
		}
		if(FF(-1*root[1]) == 0){
			root[2] = root[1];
			break;
		}
	}
	printf("%d %d %d\n", root[2], root[1], root[0]);
}
