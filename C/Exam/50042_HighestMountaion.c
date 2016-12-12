#include <stdio.h>
#include <stdlib.h>

int main(){
	int n, m;
	int GlobalMax = 0, GlobalSec = 0, GMx, GMy, GSx, GSy;
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++){
		int max = 0, Smax = 0, my, smy;
		for(int j=0; j<m; j++){
			int tmp;
			scanf("%d", &tmp);
			if(tmp >= max){
				Smax = max;
				smy = my;
				max = tmp;
				my = j+1;
			}
			else if(tmp >= Smax){
				Smax = tmp;
				smy = j+1;
			}
			if(tmp >= GlobalMax){
				GlobalSec = GlobalMax;
				GSx = GMx;
				GSy = GMy;
				GlobalMax = tmp;
				GMx = i+1;
				GMy = j+1;
			}
			else if(tmp >= GlobalSec){
				GlobalSec = tmp;
				GSx = i+1;
				GSy = j+1;
			}
		}
		printf("%d %d\n", my, smy);
	}
	printf("%d %d\n", GMx, GMy);
	return 0;
}
