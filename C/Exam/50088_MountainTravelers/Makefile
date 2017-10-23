all: main

main: main.c travel.c
	gcc -std=c99 -O2 -c main.c -lm
	gcc -std=c99 -O2 -c travel.c -lm
	gcc -std=c99 -O2 travel.o main.o -lm
clean:
	rm *.o a.out
