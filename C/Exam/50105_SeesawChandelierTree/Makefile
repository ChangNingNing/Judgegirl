all: main construct construct_fast construct_slow 
main: main.c
	gcc -std=c99 -O2 main.c -c
construct: main.o construct.c
	gcc -std=c99 -O2 construct.c -c
	gcc -std=c99 -O2 construct.o main.o -o main
construct_fast: main.o construct_fast.c
	gcc -std=c99 -O2 construct_fast.c -c
	gcc -std=c99 -O2 construct_fast.o main.o -o main_fast
construct_slow: main.o construct_slow.c
	gcc -std=c99 -O2 construct_slow.c -c
	gcc -std=c99 -O2 construct_slow.o main.o -o main_slow
clean:
	rm *.o
