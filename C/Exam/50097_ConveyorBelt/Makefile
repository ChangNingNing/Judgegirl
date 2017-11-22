all:
	gcc -std=c99 -O2 -c main.c -lm
	gcc -std=c99 -O2 -c transmission.c -lm
	gcc -std=c99 -O2 transmission.o main.o -lm
clean:
	rm *.o
