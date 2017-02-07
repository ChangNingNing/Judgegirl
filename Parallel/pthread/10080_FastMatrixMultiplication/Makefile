matrix.out: matrix.h matrix.c main.c
	gcc -std=c99 -O2 matrix.h matrix.c main.c -o matrix -lpthread -lm
	gcc -std=c99 -O2 matrix.h matrix_pthread.c main.c -o matrix_pthread -lpthread -lm
debug:
	gcc -std=c99 -O2 -DDEBUG matrix.h matrix_pthread.c main.c -o matrix_pthread -lpthread -lm
