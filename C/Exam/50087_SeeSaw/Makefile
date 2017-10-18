all: main test main_fast

main: main.c
	gcc -std=c99 -O2 main.c -o main
main_fast: main_fast.c
	gcc -std=c99 -O2 main_fast.c -o main_fast
test: test.c
	gcc -std=c99 -O2 test.c -o test
clean:
	rm main
