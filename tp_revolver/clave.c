#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>

key_t crearClave()
{
    key_t clave;
    clave = ftok("/bin/ls", 33);
    if (clave == (key_t)-1)
    {
        printf("Error: No se pudo crear la clave!\n!!!");
        exit(0);
    }
    return clave;
}
