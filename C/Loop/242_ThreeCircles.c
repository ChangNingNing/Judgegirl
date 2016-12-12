#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int caseN, i, j, k;
	scanf("%d", &caseN);
	while(caseN--){
		int X[3], Y[3], R[3];
		int minX=20000000, maxX=-20000000, minY=20000000, maxY=-20000000;
		int answerN = 0;
		for(i=0; i<3; i++){
			scanf("%d %d %d", &X[i], &Y[i], &R[i]);
			if(X[i] - R[i] < minX)
				minX = X[i] - R[i];
			if(X[i] + R[i] > maxX)
				maxX = X[i] + R[i];
			if(Y[i] - R[i] < minY)
				minY = Y[i] - R[i];
			if(Y[i] + R[i] > maxY)
				maxY = Y[i] + R[i];
		}
		for(i=maxY; i>=minY; i--){
			int test, testX;
			for(j=minX; j<=maxX; j++){
				test = testX = 0;
				for(k=0; k<3; k++){
					if(j > X[k]+R[k] || j < X[k]-R[k]){
						testX++;
						if(i > Y[k]+R[k] || i < Y[k]-R[k]){
							test++;
						}
					}
				}
				if(test==3){
					break;
				}
				if(testX==3){
					int tmpMinX = 20000000;
					for(k=0; k<3; k++){
						if(j < X[k]-R[k]){
							if(X[k]-R[k] < tmpMinX){
								tmpMinX = X[k]-R[k];
							}
						}
					}
					j = tmpMinX - 1;
				}
				int includeN = 0;
				for(k=0; k<3; k++){
					if(pow(i-Y[k], 2)+pow(j-X[k], 2) <= pow(R[k], 2))
						includeN++;
				}
				if(includeN % 2 == 1)
					answerN++;
			}
			if(test == 3){
				int tmpMaxY = -20000000;
				for(k=0; k<3; k++){
					if(i > Y[k]+R[k]){
						if(Y[k]+R[k] > tmpMaxY){
							tmpMaxY = Y[k]+R[k];
						}
					}
				}
				i = tmpMaxY + 1;
			}
		}
		printf("%d\n", answerN);
	}
	return 0;
}