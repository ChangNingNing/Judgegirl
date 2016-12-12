#include <stdio.h>
#include <stdlib.h>

int A[65538] = {0};

int main(){
	char fName[201];
	scanf("%s", fName);
	
	FILE *fin = fopen(fName, "rb");
	int a;
	fread(&a, sizeof(int), 1, fin);
	int max = -1;
	int maxP;
	for(int i=0; i<a; i++){
		short temp;
		fread(&temp, sizeof(short), 1, fin);
		A[temp+32768]++;
		if(A[temp+32768] > max){
			max = A[temp+32768];
			maxP = temp;
		}
		else if(A[temp+32768]==max && temp>maxP){
			maxP = temp;
		}
	}
	printf("%d\n%d\n", maxP, max);
	fclose(fin);
	return 0;
}
