#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "def.h"

int main(int argc, char *argv[]){
    int alguien_acerto=0;
    int numero_pensado;
    pthread_t *idHilo;
    pthread_attr_t atributos;
    
    if(argc != 2) {
        printf("Error: Debes ingresar un número como argumento\n");
        return 1;
    }
    
    int numero = atoi(argv[1]);
    printf("Se inicializo el juego con %d jugadores\n", numero);
    
    numero_pensado = rand() % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;
    printf("El numero pensado es: %d\n", numero_pensado);

    while(alguien_acerto == 0){
    }

}