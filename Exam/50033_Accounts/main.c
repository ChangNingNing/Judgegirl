#include <stdio.h>
#include <stdlib.h>
#include "account.h"

#define AGE 1
#define ZIPCODE 2

Account account[100001];

int comByNum(const void *a, const void *b){
	Account A = *(Account *)a, B = *(Account *)b;
	return A.accountNum - B.accountNum;
}

int comByZip(const void *a, const void *b){
	Account A = *(Account *)a, B = *(Account *)b;
	return A.zipcode - B.zipcode;
}

int comByAge(const void *a, const void *b){
	Account A = *(Account *)a, B = *(Account *)b;
	return A.age - B.age;
}

int main(){
	char fName[128];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "rb");
	size_t num;
	num = fread(account, sizeof(Account), 100000, fin);

	qsort(account, num, sizeof(account[0]), comByNum);
	printf("account, age, zipcode, balance\n");
	for(int i=0; i<num; i++)
		printf("%d, %d, %d, %d\n", account[i].accountNum, account[i].age, account[i].zipcode, account[i].balance);

	#if defined(SORTBY) && SORTBY == ZIPCODE
	qsort(account, num, sizeof(account[0]), comByZip);
	printf("zipcode, sum_balance\n");
	int sum = 0;
	for(int i=0; i<num; i++){
		if(i!=num-1 && account[i].zipcode == account[i+1].zipcode)
			sum += account[i].balance;
		else{
			printf("%d, %d\n", account[i].zipcode, sum+account[i].balance);
			sum = 0;
		}
	}
	#endif
	#if defined(SORTBY) && SORTBY == AGE
	qsort(account, num, sizeof(account[0]), comByAge);
	printf("age, sum_balance\n");
	int sum = 0;
	for(int i=0; i<num; i++){
		if(i!=num-1 && account[i].age == account[i+1].age)
			sum += account[i].balance;
		else{
			printf("%d, %d\n", account[i].age, sum+account[i].balance);
			sum = 0;
		}
	}
	#endif
	return 0;
}
