matrix.out: matrix.h matrix.c main.c
	gcc -std=c99 -O2 matrix.h matrix.c main.c -o matrix -fopenmp -lm
	gcc -std=c99 -O2 matrix.h matrix_omp.c main.c -o matrix_omp -fopenmp -lm
debug:
	gcc -std=c99 -O2 -DDEBUG matrix.h matrix.c main.c -o matrix -fopenmp -lm
