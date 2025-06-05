#ifndef THREAD_JUGADOR_H
#define THREAD_JUGADOR_H

void* thread_jugador(void* arg);

typedef struct {
    int id;
    int *vector_tambor;
    int vivo;
} ThreadArgs;

#endif

