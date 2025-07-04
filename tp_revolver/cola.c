#include "stdlib.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/ipc.h"
#include "def.h"
#include "unistd.h"
#include "memoria.h"
#include "sys/shm.h"
#include "sys/msg.h"
#include "clave.h"
#include "cola.h"

int creo_id_cola_mensajes(){
	int id_cola_mensajes;
	id_cola_mensajes = msgget(crearClave(), 0600 | IPC_CREAT);
	if(id_cola_mensajes == -1)
	{
		printf("Error al obtener identificador para cola mensajes\n");
		exit(-1);
	}
	return id_cola_mensajes;

}

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg){
	msgbuf msg;
	msg.long_dest = rLongDest;
	msg.int_rte = rIntRte;
	msg.int_evento = rIntEvento;
	strcpy(msg.char_mensaje, rpCharMsg);
	return msgsnd(id_cola_mensajes, &msg, sizeof(msgbuf) - sizeof(long), IPC_NOWAIT);
}

int recibir_mensaje(int id_cola_mensajes, long rLongDest, msgbuf* rMsg){
	msgbuf msg;
	int res;
	res = msgrcv(id_cola_mensajes, &msg, sizeof(msgbuf) - sizeof(long), rLongDest, 0);
	rMsg->long_dest = msg.long_dest;
	rMsg->int_rte = msg.int_rte;
	rMsg->int_evento = msg.int_evento;
	strcpy(rMsg->char_mensaje, msg.char_mensaje);
	return res;
}


int borrar_mensajes(int id_cola_mensajes){
	msgbuf msg;
	int res;
	do{
		res = msgrcv(id_cola_mensajes, &msg, sizeof(msgbuf) - sizeof(long), 0, IPC_NOWAIT);
	}while(res>0);
	return res;
}
