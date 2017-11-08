all: main

main: main.c chasing.c
	gcc -std=c99 -O2 -c chasing.c
	gcc -std=c99 -O2 -c main.c
	gcc -std=c99 -O2 chasing.o main.o -o main
clean:
	rm *.o main
