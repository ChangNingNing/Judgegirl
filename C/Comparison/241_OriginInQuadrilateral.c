#include <stdio.h>
#include <stdlib.h>

int main(){
	int node[10];
	int i;
	for(i=0; i<8; i++)
		scanf("%d", &node[i]);
	node[8] = node[0];
	node[9] = node[1];
	for(i=0; i<8; i+=2){
		if(node[i]*node[i+3] - node[i+1]*node[i+2] <= 0)
			break;
	}
	if(i==8) printf("1\n");
	else printf("0\n");
	return 0;
}
