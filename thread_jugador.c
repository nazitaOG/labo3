#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "def.h"
#include "thread_jugador.h"
#include "global.h"

void *thread_jugador(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int tiempo_espera;
    int numeros_ya_pensados[NUM_MAX] = {0};
    int cantidad_numeros_ya_pensados = 0;
    int i;

    while (1)
    {

        /* si alguien ya acertó, termino el thread*/

        pthread_mutex_lock(&mutex);
        if (*(args->alguien_acerto))
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        /* simulo que tarda en pensar*/
        tiempo_espera = (rand() % (TIEMPO_MAX - TIEMPO_MIN + 1)) + TIEMPO_MIN;
        usleep(tiempo_espera * 1000);

        /* genero un numero aleatorio*/
        args->numero_pensado_jugador = rand() % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;
        args->intentos++;
        printf("║  Jugador %d pensó en el número %d    ║\n", args->id_jugador, args->numero_pensado_jugador);

        for (i = 0; i <= cantidad_numeros_ya_pensados; i++)
        {
            if (numeros_ya_pensados[i] == args->numero_pensado_jugador)
            {   
                printf("Ups, ya habia pensado ese numero, lo vuelvo a pensar!\n");

                /* simulo que tarda en pensar*/
                tiempo_espera = (rand() % (TIEMPO_MAX - TIEMPO_MIN + 1)) + TIEMPO_MIN;
                usleep(tiempo_espera * 1000);

                /* genero un numero aleatorio*/
                args->numero_pensado_jugador = rand() % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;
                args->intentos++;
                printf("║  Jugador %d pensó en el número %d    ║\n", args->id_jugador, args->numero_pensado_jugador);

                i = 0;
            }
        }

        numeros_ya_pensados[cantidad_numeros_ya_pensados] = args->numero_pensado_jugador;
        cantidad_numeros_ya_pensados++;

        pthread_mutex_lock(&mutex);
        if (*(args->alguien_acerto) == 0 && args->numero_pensado_jugador == args->numero_pensado_pensador)
        {
            printf("║  Jugador %d acertó el número %d    ║\n", args->id_jugador, args->numero_pensado_jugador);
            *(args->alguien_acerto) = 1;
            pthread_mutex_unlock(&mutex);
            break;
        }
        if(*(args->alguien_acerto) == 1 && args->numero_pensado_jugador == args->numero_pensado_pensador){
            printf("Otro jugador ya acerto el numero, el numero del jugador %d no va ser validado\n", args->id_jugador);
            args->numero_pensado_jugador = -1;
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        
    }
    pthread_exit((void *)"Listo");
}
