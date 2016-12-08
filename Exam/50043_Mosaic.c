#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
	int x[3];
	int y[3];
	int minX=INT_MAX, maxX=INT_MIN, minY=INT_MAX, maxY=INT_MIN;
	for(int i=0; i<3; i++){
		scanf("%d %d", &x[i], &y[i]);
		if(x[i]<minX) minX = x[i];
		if(x[i]>maxX) maxX = x[i];
		if(y[i]<minY) minY = y[i];
		if(y[i]>maxY) maxY = y[i];
	}
	int v1[2][2], v2[2][2];
	v1[0][0] = x[1] - x[0];
	v1[0][1] = y[1] - y[0];
	v1[1][0] = x[2] - x[0];
	v1[1][1] = y[2] - y[0];

	v2[0][0] = -1*v1[0][0];
	v2[0][1] = -1*v1[0][1];
	v2[1][0] = x[2] - x[1];
	v2[1][1] = y[2] - y[1];
	
	int ans = 0;
	for(int i=minX; i<=maxX; i++){
		for(int j=minY; j<=maxY; j++){
			int tmpV1[2], tmpV2[2];
			tmpV1[0] = i-x[0];
			tmpV1[1] = j-y[0];
			tmpV2[0] = i-x[1];
			tmpV2[1] = j-y[1];
			if((long long)(v1[0][0]*tmpV1[1]-v1[0][1]*tmpV1[0])*(v1[1][0]*tmpV1[1]-v1[1][1]*tmpV1[0])<=0
				&& (long long)(v2[0][0]*tmpV2[1]-v2[0][1]*tmpV2[0])*(v2[1][0]*tmpV2[1]-v2[1][1]*tmpV2[0])<=0){	
				if((long long)(v1[0][0]*tmpV1[1]-v1[0][1]*(tmpV1[0]-1))*(v1[1][0]*tmpV1[1]-v1[1][1]*(tmpV1[0]-1))>0) continue;
				if((long long)(v2[0][0]*tmpV2[1]-v2[0][1]*(tmpV2[0]-1))*(v2[1][0]*tmpV2[1]-v2[1][1]*(tmpV2[0]-1))>0) continue;
				if((long long)(v1[0][0]*(tmpV1[1]-1)-v1[0][1]*tmpV1[0])*(v1[1][0]*(tmpV1[1]-1)-v1[1][1]*tmpV1[0])>0) continue;
				if((long long)(v2[0][0]*(tmpV2[1]-1)-v2[0][1]*tmpV2[0])*(v2[1][0]*(tmpV2[1]-1)-v2[1][1]*tmpV2[0])>0) continue;
				if((long long)(v1[0][0]*(tmpV1[1]-1)-v1[0][1]*(tmpV1[0]-1))*(v1[1][0]*(tmpV1[1]-1)-v1[1][1]*(tmpV1[0]-1))>0) continue;
				if((long long)(v2[0][0]*(tmpV2[1]-1)-v2[0][1]*(tmpV2[0]-1))*(v2[1][0]*(tmpV2[1]-1)-v2[1][1]*(tmpV2[0]-1))>0) continue;
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
