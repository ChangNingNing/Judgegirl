all: main

main: main.cu
	nvcc -Xcompiler "-O2 -fopenmp" main.cu -o main
clean:
	rm main
