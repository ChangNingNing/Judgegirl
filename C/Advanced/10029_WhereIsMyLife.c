#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Min(x, y) (x<y? x: y)
/* Ax = y, find x */
double A[101][101] = {0};
double y[101] = {0};
double x[101] = {0};
int isSure[101] = {0};
double input[101] = {0};
int N, M;

void mySwap(int r1, int r2){
	double tmp[101], tmpY;
	memcpy(tmp, A[r1], sizeof(A[0]));
	tmpY = y[r1];
	
	memcpy(A[r1], A[r2], sizeof(A[0]));
	y[r1] = y[r2];

	memcpy(A[r2], tmp, sizeof(A[0]));
	y[r2] = tmpY;
	return;
}

int isZero(double x){
	if(x <= 0.0001 && x >= -0.0001) return 1;
	return 0;
}

int main(){
	while(scanf("%d %d", &N, &M)!=EOF){
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++) scanf("%lf", &A[i][j]);
			scanf("%lf", &y[i]);
		}
		for(int j=0; j<M; j++) scanf("%lf", &input[j]);
		
		for(int i=0; i<N && i<M; i++){
			if(isZero(A[i][i])){
				A[i][i] = 0;
				for(int j=i+1; j<N; j++){
					if(!isZero(A[j][i])){
						mySwap(i, j);
						break;
					}
				}
			}
			if(isZero(A[i][i])){
				A[i][i] = 0;
				continue;
			}
			double pivot = A[i][i];
			for(int j=i; j<M; j++) A[i][j] /= pivot;
			y[i] /= pivot;

			for(int j=i+1; j<N; j++){
				if(isZero(A[j][i])){
					A[j][i] = 0;
					continue;
				}
				double scale = A[j][i];
				for(int k=i; k<M; k++){
					A[j][k] -= A[i][k] * scale;
				}
				y[j] -= y[i]*scale;
			}
			
		}

		int flag = -1; /* 2:contradictory; 1:not sure; 0:solution */
		for(int i=M; i<N; i++){
			if(!isZero(y[i])){
				flag = 2;
				break;
			}
		}

		if(flag==2){
			printf("contradictory\n");
			continue;
		}

		memset(x, 0, sizeof(x));
		memset(isSure, 0, sizeof(isSure));
		for(int i=Min(N, M)-1; i>=0; i--){
			int index;
			for(index=i; index<M; index++) if(!isZero(A[i][index])) break;
			if(isZero(A[i][index])) continue;
			flag = 0;
			double sum = 0;
			if(isSure[index]){
				for(int j=index; j<M; j++){
					if(A[i][j] && isSure[j]) sum += A[i][j]*x[j];
					else if(A[i][j]){
						flag = 1;
						break;
					}
				}
				if(flag==0){
					if(!isZero(y[i]-sum)){
						flag = 2;
						break;
					}
				}
			}
			else{
				for(int j=index+1; j<M; j++){
					if(A[i][j] && isSure[j]) sum += A[i][j]*x[j];
					else if(A[i][j]){
						flag = 1;
						break;
					}
				}
				if(flag==0){
					x[index] = (y[i] - sum)/A[i][index];
					isSure[index] = 1;
				}
			}
		}

		if(flag<0){
			for(int i=0; i<N && i<M; i++){
				if(!isZero(y[i])){
					flag = 2;
					break;
				}
			}
		}

		if(flag==2){
			printf("contradictory\n");
			continue;
		}

		flag = 0;
		double sum = 0;
		for(int i=0; i<M; i++){
			if(input[i]==1){
				if(isSure[i]) sum += input[i]*x[i];
				else{
					flag = 1;
					break;
				}
			}
		}
		if(flag==1){
			printf("not sure\n");
			continue;
		}
		printf("%.0lf\n", sum);
	}
	return 0;
}
