#ifndef _ARCHIVOS
#define _ARCHIVOS

int abrirArchivo(char *modo);
int abrirArchivoPorPath(char *path, char *modo);
void cerrarArchivo();
void leerLinea(char *texto);
void leerArchivo(char *texto);
void leerLineaBucle(char *texto, int fila);
void escribirLinea(char *texto);
void leerIntArchivo(int *num);
int leerIntArchivoConVerificacion(int *num);
void escribirIntArchivo(int num);
int finDeArchivo();
void eliminarArchivo();
void renombrar(char *nomViejo, char *nomNuevo);
int cantLineas();

#endif
