#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "semaforo.h"
#include "clave.h"

int semaforo;

void crearSemaforo(){
    semaforo = semget (crearClave(), 1, 0600|IPC_CREAT);

    if (semaforo == - 1){
        printf("Error: No se pudo crear el semáforo!");
        exit(0);
    }
}

void iniciarSemaforo(int valor){
    semctl(semaforo, 0, SETVAL, valor);
}

void levantarSemaforo(){
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    semop(semaforo, &operacion, 1);
}

void esperarSemaforo(){
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop(semaforo, &operacion, 1);
}
