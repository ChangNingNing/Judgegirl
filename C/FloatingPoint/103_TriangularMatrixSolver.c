#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	scanf("%d", &n);
	double M[n][n];
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			scanf("%lf", &M[i][j]);
	}
	double y[n];
	for(int i=0; i<n; i++)
		scanf("%lf", &y[i]);
	
	double x[n];
	for(int i=n-1; i>=0; i--){
		double sum = 0;
		for(int j=i+1; j<n; j++){
			sum += M[i][j]*x[j];
		}
		x[i] = (y[i]-sum)/M[i][i];
	}
	for(int i=0; i<n; i++)
		printf("%f\n", x[i]);
}
