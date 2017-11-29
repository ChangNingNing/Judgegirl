all: main main_fast testdata

main: main.c
	gcc -std=c99 -O2 main.c -o main
main_fast: main_fast.c main_fast2.c
	gcc -std=c99 -O2 main_fast.c -o main_fast
	gcc -std=c99 -O2 main_fast2.c -o main_fast2
testdata: testdata.c testdata2.c
	gcc -std=c99 -O2 testdata.c -o testdata
	gcc -std=c99 -O2 testdata2.c -o testdata2
