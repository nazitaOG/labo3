/* File: thread_jugador_bingo.c */
#include "thread_jugador_bingo.h"
#include "def.h"
#include "global.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *thread_jugador_bingo(void *arg)
{
    ThreadJugadorBingo *args = (ThreadJugadorBingo *)arg;
    int carton[5] = {0};
    int i, j;
    int cantidad_de_aciertos = 0;
    int repetido;
    int bolilla_actual;
    int acierto_actual;

    /* Genero el cartón sin repetidos */
    for (i = 0; i < 5; i++)
    {
        do
        {
            repetido = 0;
            carton[i] = rand() % (NUMERO_MINIMO - NUMERO_MAXIMO - 1) + NUMERO_MINIMO;
            for (j = 0; j < i; j++)
            {
                if (carton[j] == carton[i])
                {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);
    }

    printf("El jugador %d penso el carton: ", args->id_jugador + 1);
    for (i = 0; i < 5; i++)
    {
        printf("%d ", carton[i]);
    }
    printf("\n");

    /* Bucle principal de espera/proceso */
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (g_carton_lleno == 1)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        acierto_actual = 0;
        /* Espero a que el bolillero saque una nueva bolilla */
        pthread_mutex_lock(&mutex);
        while (args->esperar[args->id_jugador] == 0 && g_carton_lleno == 0)
        {
            pthread_mutex_unlock(&mutex);
            usleep(TIEMPO_MIN * 1000);
            printf("El jugador %d esta esperando a que el bolillero gire...\n", args->id_jugador + 1);
            
            pthread_mutex_lock(&mutex);
        }
        pthread_mutex_unlock(&mutex);

        /* Proceso la bolilla recién sacada */
        pthread_mutex_lock(&mutex);
        

        bolilla_actual = args->bolillas[*(args->cantidad_bolillas_extraidas) - 1];
        
        for (i = 0; i < 5; i++)
        {
            if (carton[i] == bolilla_actual)
            {
                cantidad_de_aciertos++;
                acierto_actual = 1;
                printf("El jugador %d ha ACERTADO el numero %d\n", args->id_jugador + 1, bolilla_actual);
                printf("CANTIDAD de ACIERTOS del jugador %d: %d\n", args->id_jugador + 1, cantidad_de_aciertos);
                break;  /* Salgo del for tras el primer match */
            }
        }

        if (acierto_actual == 0){
            printf("El jugador %d NO ha acertado el numero %d\n", args->id_jugador + 1, bolilla_actual);
        }

        /* <-- AQUÍ cambiamos a 0 para la próxima bolilla */
        args->esperar[args->id_jugador] = 0;
        pthread_mutex_unlock(&mutex);

        /* Si llenó el cartón, anuncio y salgo */
        if (cantidad_de_aciertos == 5)
        {
            pthread_mutex_lock(&mutex);
            g_carton_lleno = 1;
            pthread_mutex_unlock(&mutex);
            break;
        }
    }

    args->aciertos = cantidad_de_aciertos;
    pthread_exit((void *)"Listo");
}
