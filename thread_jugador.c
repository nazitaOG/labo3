#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "thread_jugador.h"
#include "cola.h"
#include "global.h"
#include "def.h"
#include "funciones.h"

void *thread_jugador(void *arg)
{
    ThreadArgs args = *((ThreadArgs *)arg);
    int id_cola_mensajes;
    int posicion_tambor;
    msgbuf msg;
    char buffer[2];
    int done = 0;

    id_cola_mensajes = creo_id_cola_mensajes();


    while (done == 0)
    {
        pthread_mutex_lock(&mutex);
        recibir_mensaje(id_cola_mensajes, args.id, &msg);

        if (msg.int_evento == EVT_INICIO)
        {
            printf("Soy el jugador %d y voy a dispararme\n", args.id);

            for (posicion_tambor = 0; posicion_tambor < 6; posicion_tambor++)
            {
                if (args.vector_tambor[posicion_tambor] == 0)
                {
                    args.vector_tambor[posicion_tambor] = 1;
                    break;
                }
            }

            printf("Soy el jugador %d y la posicion del tambor es %d\n", args.id, posicion_tambor);
            sprintf(buffer, "%d", posicion_tambor);
            enviar_mensaje(id_cola_mensajes, REVOLVER, args.id, EVT_DISPARO, buffer);
        }
        if (msg.int_evento == EVT_FIN)
        {
            printf("Soy el jugador %d y me mataron\n", args.id);
            args.vivo = FALSE;
            done = 1;

        }
        if (msg.int_evento == EVT_SALVADO)
        {
            printf("Soy el jugador %d y me salvaron\n", args.id);
            args.vivo = TRUE;
            done = 1;
        }

        pthread_mutex_unlock(&mutex);
        usleep(ESPERA * 1000);
    }

    pthread_exit((void *)NULL);
}
