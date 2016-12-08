#include <stdio.h>
#include <stdlib.h>

int input[65536] = {0};
int N = 0;

int main(){
	while(scanf("%d", &input[N])!=EOF) N++;

	#ifdef HUNDRED
	double average = 0;
	for(int i=0; i<N; i++){
		printf("%d ", input[i]);
		average += input[i];
	}
	average /= N;
	printf("%.1f\n", average);
	#endif

	#ifdef APLUS
	double rank = 0, grade = 0;
	for(int i=0; i<N; i++){
		if(input[i]>=90){
			printf("A+ ");
			rank += 4.3;
			grade += 95;
		}
		else if(input[i]>=85){
			printf("A ");
			rank += 4.0;
			grade += 87;
		}
		else if(input[i]>=80){
			printf("A- ");
			rank += 3.7;
			grade += 82;
		}
		else if(input[i]>=77){
			printf("B+ ");
			rank += 3.3;
			grade += 78;
		}
		else if(input[i]>=73){
			printf("B ");
			rank += 3.0;
			grade += 75;
		}
		else if(input[i]>=70){
			printf("B- ");
			rank += 2.7;
			grade += 70;
		}
		else if(input[i]>=67){
			printf("C+ ");
			rank += 2.3;
			grade += 68;
		}
		else if(input[i]>=63){
			printf("C ");
			rank += 2.0;
			grade += 65;
		}
		else if(input[i]>=60){
			printf("C- ");
			rank += 1.7;
			grade += 60;
		}
		else{
			printf("F ");
			rank += 0;
			grade += 50;
		}
	}
	rank /= N;
	grade /= N;
	printf("%.1f %.1f\n", rank, grade);
	#endif
	return 0;
}
