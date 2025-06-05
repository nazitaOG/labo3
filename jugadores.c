#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "def.h"
#include "memoria.h"
#include "semaforo.h"
#include "cola.h"
#include "thread_jugador.h"

int main(int argc, char *argv[]){
    int *listo = NULL;
    int id_cola_mensajes;
    int i;
    int vector_tambor[6] = {0, 0, 0, 0, 0, 0};
    pthread_t *idHilo;
    pthread_attr_t atributos;
    ThreadArgs *args;

    id_cola_mensajes = creo_id_cola_mensajes();
    borrar_mensajes(id_cola_mensajes);

    listo = (int *)crearMemoria(sizeof(int));

    crearSemaforo();
    esperarSemaforo();
    if (*listo != 0 && *listo != 1) {
        *listo = 0;
    }
    (*listo)++;
    levantarSemaforo();
    usleep(ESPERA * 1000);

    while(TRUE){
        esperarSemaforo();
        if (*listo == 2){
            levantarSemaforo();
            break;
        }
        levantarSemaforo();
        usleep(ESPERA * 1000);
    }

    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * CANT_JUGADORES);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < CANT_JUGADORES; i++){
        args = (ThreadArgs *)malloc(sizeof(ThreadArgs));
        args->id = i+2;
        args->vector_tambor = vector_tambor;
        args->vivo = TRUE;
        pthread_create(&idHilo[i], &atributos, thread_jugador, args);
    }

    for (i = 0; i < CANT_JUGADORES; i++){
        pthread_join(idHilo[i], NULL);
        printf("el jugador %d me devolvio el estado de vivo: %d\n", i, args[i].vivo);
        if(args[i].vivo == FALSE){
            printf("El jugador %d murio\n", i);
        }
        else{
            printf("El jugador %d sobrevivio\n", i);
        }
    }

    
    free(idHilo);
    free(args);
    desasociarMemoria((char *)listo);
    destruirMemoria();

    return 0;
}
