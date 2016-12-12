all: main.c time.c
	gcc -std=c99 -O2 -c main.c
	gcc -std=c99 -O2 -c time.c -o h12.o
	gcc -std=c99 -O2 -c time.c -o h24.o -DH24 -DinitTime=initTime24 -DsetTime=setTime24 -DaddTime=addTime24 -DprintTime=printTime24
	gcc -std=c99 -O2 main.c h12.o h24.o
12: main.c time.c
	gcc -std=c99 -O2 -c main.c
	gcc -std=c99 -O2 -c time.c -o h12.o
	gcc -std=c99 -O2 main.c h12.o -o time12
24: main.c time.c
	gcc -std=c99 -O2 -c main.c
	gcc -std=c99 -O2 -c time.c -o h24.o -DH24
	gcc -std=c99 -O2 main.c h24.o -o time24
	
