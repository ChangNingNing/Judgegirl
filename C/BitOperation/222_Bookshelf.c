#include <stdio.h>
#include <stdlib.h>

int main(){
	long long int answer = 0;
	long long int book;
	while(scanf("%lld", &book)!=EOF){
		int i;
		for(i=0; i<64; i+=8){
			if(((answer>>i)&0xff) == book){
				answer ^= (book << i);
				long long int temp1 = (answer >> i) << i;
				long long int temp2 = answer ^ temp1;
				answer ^= temp2;
				answer += temp2<<8;
				answer += book;
				break;
			}
		}
		if(i==64){
			answer = answer << 8;
			answer += book;
		}
	}
	for(int i=56; i>=0; i=i-8){
		printf("%d", (answer>>i)&0xff);
		if(i!=0) printf(" ");
	}
	printf("\n");
	return 0;
}
