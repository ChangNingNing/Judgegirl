#include <stdio.h>
#include <stdlib.h>

int A[11][11] = {0};
int Mine[11][11] = {0};

void Minus(int x, int y){
	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){
			A[x+i][y+j]--;
		}
	}
	return;
}

void Plus(int x, int y){
	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){
			A[x+i][y+j]++;
		}
	}
	return;
}

int Check(){
	for(int i=1; i<10; i++){
		for(int j=1; j<10; j++){
			if(A[i][j]!=0) return 0;
		}
	}
	return 1;
}

int try(int x, int y){
	if(y > 9) return Check();
	for(int i=1; i<y-1; i++){
		for(int j=1; j<10; j++){
			if(A[j][i]!=0) return 0;
		}
	}

	int isAns = 1;
	if(x==9) isAns = try(1, y+1);
	else isAns = try(x+1, y);
	
	if(isAns) return 1;

	Minus(x, y);
	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){
			if(A[x+i][y+j]<0 && (x+i<10 && x+i>0) && (y+j<10 && y+j>0)){
				Plus(x, y);
				return 0;
			}
		}
	}
	Mine[x][y] = 1;

	if(x==9) isAns = try(1, y+1);
	else isAns = try(x+1, y);

	if(!isAns){
		Plus(x, y);
		Mine[x][y] = 0;
	}
	return isAns;
}

int main(){
	for(int i=1; i<10; i++){
		for(int j=1; j<10; j++){
			scanf("%d", &A[i][j]);
		}
	}
	int isAns = try(1, 1);

	if(isAns){
		for(int i=1; i<10; i++){
			for(int j=1; j<10; j++){
				if(j!=1) printf(" ");
				printf("%d", Mine[i][j]);
			}
			printf("\n");
		}
	}
	else printf("no solution\n");

	return 0;
}
