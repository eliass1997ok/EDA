#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
//Importaciones para limpiar la salida, ya sea en sistemas operativos windows, o linux
#ifdef __unix__
 #define LIMPIA "clear"
#endif
#ifdef __WIN32__
 #define LIMPIA "cls"
#endif
//Función encargada de mostrar el tablero al usuario de forma más gráfica.
void mostrarTablero(int filas, int columnas, int x, int y, char modo, int tablero[filas][columnas], int tableroBombas[filas][columnas], int inicio);

//Función que permite validar las cantidades de filas y columnas ingresadas por el usuario.
int validarCantidades(int i, int j);

//Función que genera el tablero con bombas, posterior a la primera jugada del usuario.
void generarTablero(int numeroMinas, int columnas, int filas, int posicionesConBombas[filas][columnas], int x, int y);

//Función que permite al usuario ingresar su primera jugada.
void primeraJugada(int filas, int columnas, int numeroMinas,int tablero[filas][columnas], int tableroMostrar[filas][columnas], int tableroPosiciones[filas][columnas]);

//Función que valida la jugada del usurario, permitiendo que ingrese solamente una posicion dentro del tablero.
int validarJugadas(int i, int j, int filas, int columnas);

//Función que permite iniciar el juego.
void iniciarJuego();