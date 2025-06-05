#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "def.h"
#include "memoria.h"
#include "semaforo.h"
#include "cola.h"
#include "thread_jugador.h"

int main(int argc, char *argv[])
{
    int *listo = NULL;
    int id_cola_mensajes;
    int i;
    int vector_tambor[6] = {0, 0, 0, 0, 0, 0};
    pthread_t *idHilo;
    pthread_attr_t atributos;
    ThreadArgs *args = malloc(sizeof(ThreadArgs) * CANT_JUGADORES);

    id_cola_mensajes = creo_id_cola_mensajes();
    borrar_mensajes(id_cola_mensajes);

    listo = (int *)crearMemoria(sizeof(int));
    printf("listo inicial: %d\n", *listo);

    crearSemaforo();
    iniciarSemaforo(1);
    
    esperarSemaforo();
    if (*listo == 0) {
        *listo = 1;  
    } else {
        *listo = 2;  
    }
    levantarSemaforo();
    
    while (TRUE) {
        esperarSemaforo();
        if (*listo == 2) {
            levantarSemaforo();
            break;
        }
        levantarSemaforo();
        usleep(ESPERA * 1000);
    }

    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * CANT_JUGADORES);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < CANT_JUGADORES; i++)
    {
        args[i].id = i + 2;
        args[i].vector_tambor = vector_tambor;
        args[i].vivo = TRUE;
        pthread_create(&idHilo[i], &atributos, thread_jugador, &args[i]);
    }

    for (i = 0; i < CANT_JUGADORES; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("el jugador con id %d me devolvio el estado de vivo: %d\n", args[i].id, args[i].vivo);
        if (args[i].vivo == FALSE)
        {
            printf("El jugador con id %d murio\n", args[i].id);
        }
        else
        {
            printf("El jugador con id %d sobrevivio\n", args[i].id);
        }
    }

    free(idHilo);
    free(args);
    desasociarMemoria((char *)listo);
    destruirMemoria();

    return 0;
}
