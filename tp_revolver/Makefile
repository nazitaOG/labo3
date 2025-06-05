CC = gcc-4.1
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89 -pthread
PHEADER = -I./
MISC = memoria.c semaforo.c clave.c cola.c thread_jugador.c global.c funciones.c
MISH = def.h memoria.h semaforo.h clave.h cola.h thread_jugador.h global.h funciones.h
PROG1 = revolver
PROG2 = jugadores

all: clean prog1 prog2

prog1: $(PROG1).c $(MISC) $(MISH)
	$(CC) -o $(PROG1) $(PROG1).c $(MISC) $(CFLAGS) $(PHEADER)

prog2: $(PROG2).c $(MISC) $(MISH)
	$(CC) -o $(PROG2) $(PROG2).c $(MISC) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *.o $(PROG1) $(PROG2) *.txt
