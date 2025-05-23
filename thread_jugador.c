#include "thread_jugador.h"
#include "global.h"
#include <unistd.h>
#include <pthread.h>
#include "def.h"

void *thread_jugador(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int numero_pensado;
    int tiempo_espera;
    int numeros_ya_pensados[100] = {0};
    int cantidad_numeros_ya_pensados = 0;
    int i, j;

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
        numero_pensado = rand() % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;

        for (i = 0; i <= cantidad_numeros_ya_pensados; i++)
        {
            if (numeros_ya_pensados[i] == numero_pensado)
            {

                /* simulo que tarda en pensar*/
                tiempo_espera = (rand() % (TIEMPO_MAX - TIEMPO_MIN + 1)) + TIEMPO_MIN;
                usleep(tiempo_espera * 1000);

                /* genero un numero aleatorio*/
                numero_pensado = rand() % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;

                i = 0;
            }
        }

        numeros_ya_pensados[j] = numero_pensado;
        cantidad_numeros_ya_pensados++;

        pthread_mutex_lock(&mutex);
        /* analizo si el numero pensado coincide con el pasado por argumento y termino el thread*/
        if (numero_pensado == args->numero_pensado)
        {
            *(args->alguien_acerto) = 1;
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        
    }
    pthread_exit((void *)"Listo");
}