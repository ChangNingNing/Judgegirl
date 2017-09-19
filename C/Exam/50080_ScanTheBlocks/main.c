#include <stdio.h>

int main(){
	int n;
	while (scanf("%d", &n)!=EOF){
		int tmp, num = 0;
		int max = -20000, min = 20000;
		for (; num<n && scanf("%d", &tmp)!=EOF; num++){
			if (tmp > max) max = tmp;
			if (tmp < min) min = tmp;
		}
		if (num == n) printf("%d\n", max);
		else printf("%d\n", min);
	}
	return 0;
}
