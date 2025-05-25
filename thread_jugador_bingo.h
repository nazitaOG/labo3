typedef struct ThreadJugadorBingo{
    int id_jugador;
    int *bolillas;
    int *cantidad_bolillas_extraidas;
    int *esperar;
    int aciertos;
} ThreadJugadorBingo;

void* thread_jugador_bingo(void* arg);
