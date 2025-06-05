#ifndef _COLA
#define _COLA

#include "def.h" /* para LARGO_BUFFER */

typedef struct {
    long long_dest;
    int int_rte;
    int int_evento;
    char char_mensaje[LARGO_BUFFER];
} msgbuf;

int creo_id_cola_mensajes();
int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg);
int recibir_mensaje(int id_cola_mensajes, long rLongDest, msgbuf* rMsg);
int borrar_mensajes(int id_cola_mensajes);

/* destinos posibles */
typedef enum{
    NADIE,
    REVOLVER,
    JUGADOR
} destino;

/* eventos */
typedef enum{
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_DISPARO,
    EVT_SALVADO,
    EVT_FIN
} evento;


#endif
