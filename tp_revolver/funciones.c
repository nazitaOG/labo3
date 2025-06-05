#include "def.h"
#include <stdlib.h>

int obtener_valor_aleatorio(int min, int max){
    if (min > max){
        return FALSE;
    }
    return min + rand() % (max - min + 1);
}

int obtener_valor_aleatorio_sin_repetir(int min, int max, int* valores_usados){
    int i;
    int valor;
    int repetido;

    do {
        repetido = 0;
        valor = obtener_valor_aleatorio(min, max);

        if(valor == FALSE){
            return FALSE;
        }
        
        for(i = 0; i < max; i++){
            if(valores_usados[i] == valor){
                repetido = 1;
                break;
            }
        }
    } while(repetido);
    
    return valor;
}
