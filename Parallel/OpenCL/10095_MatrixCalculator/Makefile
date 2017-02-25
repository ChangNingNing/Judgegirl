all: clean seq cl

seq:
	gcc -std=c99 -O2 sequence.c -o sequence
cl:
	gcc -std=c99 -O2 main.c -lm -lOpenCL -fopenmp -o main
clean:
	rm sequence main
