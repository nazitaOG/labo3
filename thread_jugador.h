#ifndef THREAD_JUGADOR_H
#define THREAD_JUGADOR_H

void* thread_jugador(void* arg);

typedef struct {
    int numero_pensado;
    int* alguien_acerto;
} ThreadArgs;

#endif
