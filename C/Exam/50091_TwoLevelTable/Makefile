all: main.c constructTable.c
	gcc -std=c99 -O2 -c main.c -lm
	gcc -std=c99 -O2 -c constructTable.c -lm
	gcc -std=c99 -O2 constructTable.o main.o -lm
