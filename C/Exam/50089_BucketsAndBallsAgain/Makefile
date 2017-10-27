all: main

main: main.c placement.c
	gcc -std=c99 -O2 -c main.c -lm
	gcc -std=c99 -O2 -c placement.c -lm
	gcc -std=c99 -O2 placement.o main.o -lm
clean:
	rm *.o a.out
