#ifndef _COLA
#define _COLA

#include "def.h"

int creo_id_cola_mensajes();
int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg);
int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg);
int borrar_mensajes(int id_cola_mensajes);

#endif
