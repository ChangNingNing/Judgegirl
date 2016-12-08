#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
 
int main() {
        Memory myMemory;
        
	char ins[10];
	int start, length;
	while(scanf("%s", ins)!=EOF){
		int notImportant;
		scanf("%d", &notImportant);
		switch(ins[0]){
		case 'I':
			scanf("%d", &length);
			initMemory(&myMemory, length);
			break;
		case 'A':
			scanf("%d %d", &start, &length);
			allocateMemory(&myMemory, start, length);
			break;
		case 'F':
			scanf("%d %d", &start, &length);
			freeMemory(&myMemory, start, length);
			break;
		case 'P':
			printMemory(&myMemory);
			break;
		}
	}
	return 0;
	
	
	
	
	initMemory(&myMemory, 100);
	printMemory(&myMemory);
	allocateMemory(&myMemory, 50, 10);
        printMemory(&myMemory);
        allocateMemory(&myMemory, 70, 10);
        printMemory(&myMemory);
        allocateMemory(&myMemory, 0, 10);
        printMemory(&myMemory);
        allocateMemory(&myMemory, 30, 10);
        printMemory(&myMemory);
        freeMemory(&myMemory, 50, 5);
        printMemory(&myMemory);
        freeMemory(&myMemory, 70, 10);
        printMemory(&myMemory);
        freeMemory(&myMemory, 30, 10);
        printMemory(&myMemory);
        freeMemory(&myMemory, 0, 10);
        printMemory(&myMemory);
	return 0;
}
