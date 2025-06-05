#ifndef DEF_H
#define DEF_H

#define TRUE 1
#define FALSE 0
#define LARGO_BUFFER 50
#define NUMERO_MINIMO 1
#define NUMERO_MAXIMO 20
#define TIEMPO_MIN 500
#define TIEMPO_MAX 5000

typedef struct {
    long long_dest;
    int int_rte;
    int int_evento;
    char char_mensaje[LARGO_BUFFER];
} mensaje;

#endif
