all: main1.c main2.c count.c
	gcc -std=c99 -O2 -c count.c -lm
	gcc -std=c99 -O2 -c main1.c -lm
	gcc -std=c99 -O2 -c main2.c -lm
	gcc -std=c99 -O2 count.o main1.o -o main1 -lm
	gcc -std=c99 -O2 count.o main2.o -o main2 -lm
