#include "eval.h"

int eval(int exp[]){
	int n = exp[0];
	for(int i=2; i<n; i+=2){
		if(exp[i]==1 || exp[i]==2) continue;
		else if(exp[i]==3) exp[i+1] = exp[i-1] * exp[i+1];
		else if(exp[i]==4){
			if(exp[i+1]==0) return -2147483647;
			exp[i+1] = exp[i-1] / exp[i+1];
		}
		else return -2147483646;
		exp[i-1] = exp[i] = 0;
	}

	int pre = 1;
	for(int i=2; i<n; i+=2){
		if(exp[i]==1) exp[i+1] = exp[i-1] + exp[i+1], pre = 1;
		else if(exp[i]==2) exp[i+1] = exp[i-1] - exp[i+1], pre = 2;
		else exp[i+1] = (pre==1)? (exp[i-1]+exp[i+1]): (exp[i-1]-exp[i+1]);
	}

	return exp[n];
}
