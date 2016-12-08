#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main(){
	srand(time(NULL));

	for(int i=0; i<5; i++){
		printf("%d\n", 999);
		for(int j=1; j<=999*999; j++){
			int tmp = rand() % 1000;
			printf("%d%c", tmp, j==999*999? '\n': ' ');
		}
	}
	return 0;
}
