#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "def.h"
#include "memoria.h"
#include "semaforo.h"
#include "cola.h"
#include "funciones.h"

int main(int argc, char *argv[])
{
    int *listo = NULL;
    int id_cola_mensajes;
    int valor_aleatorio;
    int i;
    msgbuf msg;

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

    srand(time(NULL));
    valor_aleatorio = obtener_valor_aleatorio(1, 6);
    printf("saque el valor aleatorio: %d\n", valor_aleatorio);

    for (i = 0; i < CANT_JUGADORES; i++)
    {
        printf("envie el mensaje al jugador %d\n", JUGADOR + i);
        enviar_mensaje(id_cola_mensajes, JUGADOR + i, REVOLVER, EVT_INICIO, "");
    }

    for (i = 0; i < CANT_JUGADORES; i++)
    {
        recibir_mensaje(id_cola_mensajes, REVOLVER, &msg);
        printf("recibi el mensaje: %s del jugador %d\n", msg.char_mensaje, JUGADOR + i);
        if (atoi(msg.char_mensaje) == valor_aleatorio)
        {
            enviar_mensaje(id_cola_mensajes, JUGADOR + i, REVOLVER, EVT_FIN, "");
        }
        else
        {
            enviar_mensaje(id_cola_mensajes, JUGADOR + i, REVOLVER, EVT_SALVADO, "");
        }
        usleep(ESPERA * 1000);
    }

    desasociarMemoria((char *)listo);
    destruirMemoria();
    return 0;
}
