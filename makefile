all: TAD/CREATE.o TAD/fornecidas.o TAD/buscar.o TAD/DELETE.o TAD/SELECT.o TAD/util.o programaTrab.o
	gcc TAD/CREATE.o TAD/fornecidas.o TAD/buscar.o TAD/DELETE.o TAD/SELECT.o TAD/SELECT_ALL.o TAD/util.o programaTrab.c -o programaTrab -std=c99 -Wall -lm

TAD/CREATE.o:
	gcc -c TAD/CREATE.c -o TAD/CREATE.o
	
TAD/fornecidas.o:
	gcc -c TAD/fornecidas.c -o TAD/fornecidas.o

TAD/buscar.o:
	gcc -c TAD/buscar.c -o TAD/buscar.o

TAD/DELETE.o:
	gcc -c TAD/DELETE.c -o TAD/DELETE.o

TAD/SELECT.o:
	gcc -c TAD/SELECT.c -o TAD/SELECT.o
	
TAD/SELECT_ALL.o:
	gcc -c TAD/SELECT_ALL.c -o TAD/SELECT_ALL.o

TAD/util.o:
	gcc -c TAD/util.c -o TAD/util.o

run:
	./programaTrab
clean:
	rm TAD/CREATE.o
	rm TAD/fornecidas.o
	rm TAD/buscar.o
	rm TAD/DELETE.o
	rm TAD/SELECT.o
	rm TAD/SELECT_ALL.o
	rm TAD/util.o
	rm programaTrab.o
	rm programaTrab

r:
	make clean
	make all
	./programaTrab