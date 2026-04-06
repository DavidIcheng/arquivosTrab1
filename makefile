all: TAD/util.o TAD/CREATE.o TAD/fornecidas.o TAD/buscar.o TAD/DELETE.o TAD/SELECT.o TAD/SELECT_ALL.o TAD/UPDATE.o programaTrab.o
	gcc TAD/util.o TAD/CREATE.o TAD/fornecidas.o TAD/buscar.o TAD/DELETE.o TAD/SELECT.o TAD/SELECT_ALL.o TAD/UPDATE.o programaTrab.c -o programaTrab -std=c99 -Wall -lm

TAD/util.o:
	gcc -c TAD/util.c -o TAD/util.o

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

TAD/UPDATE.o:
	gcc -c TAD/UPDATE.c -o TAD/UPDATE.o

run:
	./programaTrab
clean:
	rm TAD/util.o
	rm TAD/CREATE.o
	rm TAD/fornecidas.o
	rm TAD/buscar.o
	rm TAD/DELETE.o
	rm TAD/SELECT.o
	rm TAD/SELECT_ALL.o
	rm TAD/UPDATE.o
	rm programaTrab.o
	rm programaTrab

r:
	make clean
	make all
	./programaTrab