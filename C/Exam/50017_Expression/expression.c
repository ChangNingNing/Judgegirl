#include "expression.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *E;
int ptr, flag;

int myExp(){
	if(flag) return 0;
	if(E[ptr] == '-'){
		ptr += 1;
		return -1 * myExp();
	}
	if(E[ptr] == '('){
		ptr += 1;
		int ans1 = myExp();
		char  operation = E[ptr++];
		int ans2 = myExp();
		ptr += 1;
		if(operation == '+') return ans1 + ans2;
		if(operation == '-') return ans1 - ans2;
		if(operation == '*') return ans1 * ans2;
		if(operation == '/'){
			if(ans2 == 0){
				flag = 1;
				return 0;
			}
			return ans1 / ans2;
		}
	}
	if(E[ptr] <= '9' && E[ptr] >= '0'){
		ptr += 1;
		return E[ptr-1] - '0';
	}
	flag = 1;
	return 0;
}

int expression(char *string){
	E = string;
	flag = ptr = 0;
	int ans = myExp();
	if(flag || E[ptr]!='\0') return -2147483648;
	return ans;
}
