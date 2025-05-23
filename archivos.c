#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archivos.h"
#include "def.h"

FILE *fp;


int abrirArchivo(char *modo)
{
    fp = fopen(PATH_ARCHIVO, modo);

    if (fp == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

int abrirArchivoPorPath(char *path, char *modo)
{
    fp = fopen(path, modo);

    if (fp == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void cerrarArchivo()
{
    fclose(fp);
}

void leerLinea(char *texto)
{
    fscanf(fp, " %[^\n]", texto);
    fscanf(fp, "\n");
}

void leerArchivo(char *texto)
{
    fscanf(fp, " %[^\n]", texto);
    fscanf(fp, "\n");
}

void leerLineaBucle(char *texto, int fila)
{
    int i;
    for (i = 0; i < fila; i++)
    {
        leerLinea(texto);
    }
}

void escribirLinea(char *texto)
{
    if (texto[0] == '\0') {
        fprintf(fp, "-\n");  /* Escribimos un guión si el string está vacío */
    } else {
        fprintf(fp, "%s\n", texto);
    }
    fflush(fp);
}

void leerIntArchivo(int *num)
{
    fscanf(fp, "%d\n", num);
}

void escribirIntArchivo(int num)
{
    fprintf(fp, "%d\n", num);
    fflush(fp);
}

int finDeArchivo()
{
    return feof(fp);
}

void eliminarArchivo()
{
    remove(PATH_ARCHIVO);
}

void renombrar(char *nomViejo, char *nomNuevo)
{
    rename(nomViejo, nomNuevo);
}

int cantLineas()
{
    char datos[MAX_CARACTERES];
    int cant = 0;
    
    if (abrirArchivo("r"))
    {
        while (!finDeArchivo())
        {
            leerLinea(datos);
            cant++;
        }
        cerrarArchivo();
    }

    return cant;
}

int leerIntArchivoConVerificacion(int *num) {
    int leido = fscanf(fp, "%d", num);
    return (leido == 1);  /* Retorna 1 si se leyó correctamente, 0 si no */
}
