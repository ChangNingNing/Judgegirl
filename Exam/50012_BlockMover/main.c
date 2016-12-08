#include <stdio.h>
#include "blockmover.h"
 
int main() {
	for(int i=1; i<=8; i++){
		unsigned long long int tmp;
		initialize(&tmp, 0, 0, i);
		printf("0x%llX, ", tmp);
	}
	puts("");
    unsigned long long int num;
    char operation;
    int ret;
 
    scanf("%llu", &num);
 
    while (1) {
        ret = 1;
 
        scanf("%c", &operation);
 
        if (operation == 'p') {
            printBlock(&num);
            break;
        } else if (operation == 'u')
            ret = moveUp(&num);
        else if (operation == 'd')
            ret = moveDown(&num);
        else if (operation == 'l')
            ret = moveLeft(&num);
        else if (operation == 'r')
            ret = moveRight(&num);
        else if (operation == 'i') {
            int row, column, size;
            scanf("%d %d %d", &row, &column, &size);
            initialize(&num, row, column, size);
        }
 
        if (ret == 0)
            printf("Invalid move!\n");
    }
 
    return 0;
}
