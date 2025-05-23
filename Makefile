CC = gcc-4.1
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89 -pthread
PHEADER = -I./
MISC = global.c thread_jugador.c
MISH = def.h global.h thread_jugador.h
PROG1 = pensador

all: clean prog1

prog1: $(PROG1).c $(MISC) $(MISH)
	$(CC) -o $(PROG1) $(PROG1).c $(MISC) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *.o $(PROG1) $(PROG2) *.txt