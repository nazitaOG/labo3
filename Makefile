CC = gcc-4.1
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I./
MISC = clave.c cola.c funciones.c
MISH = clave.h def.h global.h cola.h funciones.h
PROG1 = banco
PROG2 = cajero_automatico

all: clean prog1 prog2

prog1: $(PROG1).c $(MISC) $(MISH)
	$(CC) -o $(PROG1) $(PROG1).c $(MISC) $(CFLAGS) $(PHEADER)

prog2: $(PROG2).c $(MISC) $(MISH)
	$(CC) -o $(PROG2) $(PROG2).c $(MISC) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *.o $(PROG1) $(PROG2) *.txt