#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "def.h"
#include "thread_jugador.h"
#include "global.h"

int main(int argc, char *argv[]){
    int alguien_acerto=0;
    int numero_pensado;
    int i;
    int numero;
    pthread_t *idHilo;
    pthread_attr_t atributos;
    ThreadArgs *args;
    
    if(argc != 2) {
        printf("Error: Debes ingresar un número como argumento\n");
        return 1;
    }
    
    numero = atoi(argv[1]);
    printf("╔════════════════════════════════════════╗\n");
    printf("║        INICIO DEL JUEGO                ║\n");
    printf("║  Jugadores registrados: %d             ║\n", numero);
    printf("╚════════════════════════════════════════╝\n");

    srand(time(NULL));
    
    numero_pensado = rand() % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;
    printf("╔════════════════════════════════════════╗\n");
    printf("║        NÚMERO PENSADO                  ║\n");
    printf("║  El número es: %d                      ║\n", numero_pensado);
    printf("╚════════════════════════════════════════╝\n");

    /*Inicializar el hilo*/
    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * numero);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    args = (ThreadArgs *)malloc(sizeof(ThreadArgs) * numero);
    for(i=0; i<numero; i++){
        args[i].numero_pensado_pensador = numero_pensado;
        args[i].alguien_acerto = &alguien_acerto;
        args[i].numero_pensado_jugador = 0;
        args[i].id_jugador = i;
        args[i].intentos = 0;
    }

    /* Inicio mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Inicio hilos */
    for (i=0; i<numero; i++){
        pthread_create(&idHilo[i], &atributos, thread_jugador, (void *)&args[i]);
    }

    /* Finalizar hilos */
    for (i=0; i<numero; i++){
        pthread_join(idHilo[i], NULL);
    }

    for (i=0; i<numero; i++){
        printf("║  Jugador %d intentó %d veces    ║\n", i, args[i].intentos);
    }
    
    for (i=0; i<numero; i++){
        if (args[i].numero_pensado_jugador == numero_pensado){
            printf("╔════════════════════════════════════════╗\n");
            printf("║           ¡JUGADOR GANADOR!            ║\n");
            printf("║      Jugador %d acertó el número %d    ║\n", i, numero_pensado);
            printf("╚════════════════════════════════════════╝\n");
        }
    }

    /* Finalizar mutex */
    pthread_attr_destroy(&atributos);
    pthread_mutex_destroy(&mutex);
    free(idHilo);
    free(args);

    return 0;
}
