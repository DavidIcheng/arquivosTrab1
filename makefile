all: TAD/CREATE.o TAD/fornecidas.o programaTrab.o
	gcc TAD/CREATE.o TAD/fornecidas.o programaTrab.c -o programaTrab -std=c99 -Wall -lm

TAD/CREATE.o:
	gcc -c TAD/CREATE.c -o TAD/CREATE.o
	
TAD/fornecidas.o:
	gcc -c TAD/fornecidas.c -o TAD/fornecidas.o

run:
	./programaTrab
clean:
	rm TAD/CREATE.o
	rm TAD/fornecidas.o
	rm programaTrab
