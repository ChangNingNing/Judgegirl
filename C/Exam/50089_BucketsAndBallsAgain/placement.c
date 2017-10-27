#include "placement.h"
#define MAXN 1024
#define MAXM 16384

void place(int bucket[MAXN],int N,int ball[MAXM],int M,int method,int result[MAXM]){
	switch (method){
	case 0:
		for (int i=0; i<M; i++){
			int f = 1;			
			for (int j=0; j<N && f; j++){
				if (bucket[j] >= ball[i]){
					bucket[j] -= ball[i];
					result[i] = j;
					f = 0;
				}
			}
			if (f) result[i] = -1;
		}
		break;
	case 1:
		for (int i=0; i<M; i++){
			int min = 2147483647, minP = -1;
			for (int j=0; j<N; j++){
				if (bucket[j] >= ball[i] && bucket[j] - ball[i] < min){
					min = bucket[j] - ball[i];
					minP = j;
				}
			}
			result[i] = minP;
			if (minP >= 0)
				bucket[minP] = min;
		}
		break;
	case 2:
		for (int i=0; i<M; i++){
			int max = -1, maxP = -1;
			for (int j=0; j<N; j++){
				if (bucket[j] >= max){
					max = bucket[j];
					maxP = j;
				}
			}
			if (max >= ball[i]){
				result[i] = maxP;
				bucket[maxP] = max - ball[i];
			}
			else
				result[i] = -1;
		}
		break;
	default:
		break;
	}
	return;
}
