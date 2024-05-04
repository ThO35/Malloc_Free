
pouet: my_malloc.o main.o
	gcc -o main my_malloc.o main.o -Wall -ansi -std=c17 -g

my_malloc.o: my_malloc.h my_malloc.c
	gcc -c -o my_malloc.o my_malloc.c -Wall -ansi -std=c17

main.o: main.c my_malloc.h
	gcc -c -o main.o main.c -Wall -ansi -std=c17

clear:
	rm -f main main.o my_malloc.o
