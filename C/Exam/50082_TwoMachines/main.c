#include <stdio.h>
int MAX(int a, int b){ return a>b? a: b; }
int main(){
	int A = 0, B = 0;
	int ar, ta, tb;
	while (scanf("%d %d %d", &ar, &ta, &tb) != EOF){
		A = MAX(ar, A) + ta;
		B = MAX(A, B) + tb;
		printf("%d\n", B);
	}
	return 0;
}
