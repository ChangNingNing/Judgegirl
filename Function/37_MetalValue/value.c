#include <stdio.h>
#include "value.h"

int value(int type, int width, int height, int length){
	int W=width, H=height, L=length;
	int price;
	switch(type){
	case 79:
		price = 30;
		break;
	case 47:
		price = 10;
		break;
	case 29:
		price = 4;
		break;
	case 82:
		price = 5;
		break;
	case 26:
		price = 3;
		break;
	case 22:
		price = 9;
		break;
	default:
		return -1;
	}
	if(width<=0 || height<=0 || length<=0) return -2;
	int gcd;
	while(width!=0){
		int temp;
		temp = width;
		width = height % width;
		height = temp;
	}
	gcd = height;
	while(length!=0){
		int temp;
		temp = length;
		length = gcd % length;
		gcd = temp;
	}
	int answer = gcd*gcd*gcd*W*H*L*price;
	return answer;
}
