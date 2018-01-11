all: main_slow main_cut main_fast main_ll main_table

main_slow: main_slow.c
	gcc -std=c99 -O2 main_slow.c -o main_slow
main_cut: main_cut.c
	gcc -std=c99 -O2 main_cut.c -o main_cut
main_fast: main_fast.c
	gcc -std=c99 -O2 main_fast.c -o main_fast
main_ll: main_ll.c
	gcc -std=c99 -O2 main_ll.c -o main_ll
main_table: main_table.c
	gcc -std=c99 -O2 main_table.c -o main_table
clean:
	rm main_slow main_cut main_fast main_ll main_table
