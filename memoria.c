#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "clave.h"
#include "memoria.h"

int idMemoria;

void *crearMemoria(int size){
    void *pMemoria;

    idMemoria = shmget(crearClave(), size, 0777 | IPC_CREAT);

    if (idMemoria == -1){
        perror("No consigo id para memoria compartida!");
        exit (0);
    }

    pMemoria = (void *)shmat(idMemoria, (char *)0, 0);

    if (pMemoria == NULL){
        perror("No consigo memoria compartida!");
        exit(0);
    }

    return pMemoria;
}

void desasociarMemoria(char *memoria){
    shmdt (memoria);
}

void destruirMemoria(){
    shmctl (idMemoria, IPC_RMID, (struct shmid_ds *)NULL);
}

