all: main main_tree main_linear
main: main.c
	gcc -std=c99 -O2 main.c -o main
main_tree: main_tree.c
	gcc -std=c99 -O2 main_tree.c -o main_tree
main_linear: main_linear.c
	gcc -std=c99 -O2 main_linear.c -o main_linear
clean:
	rm *.o
