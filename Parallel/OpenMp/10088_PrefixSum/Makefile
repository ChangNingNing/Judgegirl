all:
	gcc -std=c99 -O2 -pthread prefixsum-seq.c secret.c -o prefixsum-seq
	gcc -std=c99 -O2 -fopenmp prefixsum-omp.c secret.c -o prefixsum-omp
