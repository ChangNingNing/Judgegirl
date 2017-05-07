all: main_cl

main_cl: main.c vecdot.cl
	gcc -std=c99 -O2 main.c -lOpenCL -fopenmp -o main_cl
clean:
	rm main_cl
