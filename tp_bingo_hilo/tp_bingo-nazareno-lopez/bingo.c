#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "def.h"
#include "thread_jugador_bingo.h"
#include "global.h"

int main(int argc, char *argv[])
{
    int bolillas[NUMERO_MAXIMO] = {0};
    int cantidad_bolillas_extraidas = 0;
    int bolilla_extraida = 0;
    int cantidad_jugadores;
    int *esperar;
    int todos_listos;
    int tiempo_espera;
    int ganadores = 0;
    int i, j, k;
    pthread_t *idHilo;
    pthread_attr_t atributos;
    ThreadJugadorBingo *args;

    if (argc != 2)
    {
        printf("Error: Debes ingresar un número de jugadores\n");
        return 1;
    }

    if(atoi(argv[1]) > 9){
        printf("Error: El numero de jugadores no puede ser mayor a 9\n");
        return 1;
    }

    if(atoi(argv[1]) < 2){
        printf("Error: El numero de jugadores no puede ser menor a 2\n");
        return 1;
    }

    if(NUMERO_MINIMO > NUMERO_MAXIMO){
        printf("Error: El numero minimo no puede ser mayor al numero maximo\n");
        return 1;
    }

    if(NUMERO_MINIMO < 1){
        printf("Error: El numero minimo no puede ser menor a 1\n");
        return 1;
    }

    if(NUMERO_MAXIMO < 5){
        printf("Error: El numero maximo no puede ser menor a 6\n");
        return 1;
    }

    cantidad_jugadores = atoi(argv[1]);

    printf("╔════════════════════════════════════════╗\n");
    printf("║           INICIO DEL JUEGO             ║\n");
    printf("║       Jugadores registrados: %d        ║\n", cantidad_jugadores);
    printf("╚════════════════════════════════════════╝\n");

    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad_jugadores);
    esperar = (int *)malloc(sizeof(int) * cantidad_jugadores);
    for (i = 0; i < cantidad_jugadores; i++)
    {
        esperar[i] = 0;
    }
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    srand(time(NULL));
    args = (ThreadJugadorBingo *)malloc(sizeof(ThreadJugadorBingo) * cantidad_jugadores);
    for (i = 0; i < cantidad_jugadores; i++)
    {
        args[i].id_jugador = i;
        args[i].bolillas = bolillas;
        args[i].cantidad_bolillas_extraidas = &cantidad_bolillas_extraidas;
        args[i].esperar = esperar;
        args[i].aciertos = 0;
    }

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < cantidad_jugadores; i++)
    {
        pthread_create(&idHilo[i], &atributos, thread_jugador_bingo, (void *)&args[i]);
    }

    for (i = 0; i < NUMERO_MAXIMO; i++)
    {
        pthread_mutex_lock(&mutex);
        if (g_carton_lleno == 1)
        {
            pthread_mutex_unlock(&mutex);
            break;
        } 
        pthread_mutex_unlock(&mutex);

        if (i != 0)
        {
            do
            {
                pthread_mutex_lock(&mutex);
                todos_listos = 1;
                for (j = 0; j < cantidad_jugadores; j++)
                {
                    if (esperar[j] == 1)
                    {
                        todos_listos = 0;
                        break;
                    }
                }
                pthread_mutex_unlock(&mutex);

                if (todos_listos == 0)
                {
                    usleep(TIEMPO_MIN * 1000);
                    printf("El bolillero esta esperando a que un jugador termine de anotar...\n");
                }
            } while (todos_listos == 0);
        }

        pthread_mutex_lock(&mutex);
        if(g_carton_lleno == 1){
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);


        printf("\nGirando el bolillero...\n");
        tiempo_espera = (rand() % (TIEMPO_MAX - TIEMPO_MIN + 1)) + TIEMPO_MIN;
        usleep(tiempo_espera * 1000);
        bolilla_extraida = rand() % (NUMERO_MINIMO - NUMERO_MAXIMO - 1) + NUMERO_MINIMO;
        printf("\nLa bolilla extraida es: %d\n", bolilla_extraida);

        if (i == 0)
        {

            pthread_mutex_lock(&mutex);
            bolillas[i] = bolilla_extraida;
            cantidad_bolillas_extraidas++;
            for (j = 0; j < cantidad_jugadores; j++)
            {
                esperar[j] = 1;
            }
            pthread_mutex_unlock(&mutex);
        }
        else
        {

            for (j = 0; j < NUMERO_MAXIMO; j++)
            {
                if (bolillas[j] == bolilla_extraida)
                {
                    printf("\nLa bolilla %d ya fue extraida, TIRO DE NUEVO!\n", bolilla_extraida);
                    i--;
                    break;
                }
            }
            pthread_mutex_lock(&mutex);
            if (bolillas[j] != bolilla_extraida)
            {

                bolillas[i] = bolilla_extraida;
                cantidad_bolillas_extraidas++;
                /* Esto "despierta" a los threads */
                for (k = 0; k < cantidad_jugadores; k++)
                {

                    esperar[k] = 1;
                }
                
            }
            pthread_mutex_unlock(&mutex);
        }
    }
    for (i = 0; i < cantidad_jugadores; i++)
    {
        pthread_join(idHilo[i], NULL);
    }

    for (i = 0; i < cantidad_jugadores; i++)
    {
        printf("\nEl jugador %d tiene %d aciertos\n", args[i].id_jugador + 1, args[i].aciertos);
        if (args[i].aciertos == 5)
        {
            printf("\nEl jugador %d ha ganado el juego!\n", args[i].id_jugador + 1);
            ganadores++;
        }
    }

    if (ganadores == 0)
    {
        printf("\nNo hay ganadores, que raro...\n");
    }

    if (ganadores > 1)
    {
        printf("\nHubo un empate!\n");
    }

    pthread_attr_destroy(&atributos);
    pthread_mutex_destroy(&mutex);
    free(idHilo);
    free(args);

    return 0;
}
