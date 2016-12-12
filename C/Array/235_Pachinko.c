#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long A[4][20] = {0};

long long GCD(long long x, long long y){
	while(x != 0){
		long long temp;
		temp = x;
		x = y % x;
		y = temp;
	}
	return y;
}

void update(int index, int cursor, int preIndex, int preCursor, long long son, long long mom){
	son = A[preIndex][preCursor] * son;
	mom = A[preIndex+1][preCursor] * mom;
	long long gcd = GCD(son, mom);
	son /= gcd;
	mom /= gcd;

	if(A[index+1][cursor]){
		A[index][cursor] = A[index][cursor]*mom + son*A[index+1][cursor];
		A[index+1][cursor] *= mom;
	}
	else{
		A[index][cursor] = son;
		A[index+1][cursor] = mom;
	}
	gcd = GCD(A[index][cursor], A[index+1][cursor]);
	A[index+1][cursor] /= gcd;
	A[index][cursor] /= gcd;
}

int main(){
	int n;
	scanf("%d", &n);
	int index = 0;
	A[index][0] = 1;
	A[index+1][0] = 1;

	int cursor;
	for(int i=1; i<=n; i++){
		index = (index==2)? 0: 2;
		memset(A[index], 0, sizeof(long long)*2*20);
		cursor = 0;
		for(int j=0; j<i; j++){
			long long x1, x2, y;
			scanf("%lld %lld", &x1, &x2);
			y = x1 + x2;
			update(index, cursor, (index+2)%4, cursor, x1, y);
			update(index, cursor+1, (index+2)%4, cursor, x2, y);
			cursor++;
		}
	}

	for(int i=0; i<=cursor; i++){
		printf("%lld/%lld\n", A[index][i], A[index+1][i]);
	}

	return 0;
}
