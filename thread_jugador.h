#ifndef THREAD_JUGADOR_H
#define THREAD_JUGADOR_H

void* thread_jugador(void* arg);

typedef struct {
    int numero_pensado_pensador;
    int* alguien_acerto;
    int numero_pensado_jugador;
    int id_jugador;
    int intentos;
} ThreadArgs;

#endif
