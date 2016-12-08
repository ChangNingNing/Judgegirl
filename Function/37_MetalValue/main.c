#include <stdio.h>
#include <stdlib.h>
#include "value.h"

int main(){
	int type, width, height, length;
	scanf("%d %d %d %d", &type, &width, &height, &length);
	printf("%d\n", value(type, width, height, length));

return 0;
}
