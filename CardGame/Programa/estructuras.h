#pragma once

/**
 * @struct NodoNumeros
 * @brief La siguiente estructura corresponde a un nodo de una lista enlazada de números. 
 *        En su contenido, se tiene un número y un puntero al siguiente nodo.
 */
typedef struct nodoLista{
	int numero;
	struct nodoLista* siguiente;
}NodoNumeros;

/**
 * @struct NodoNumeros
 * @brief ListaNumeros corresponde a la estructura que permite acceder al primer y último nodo de una lista enlazada de números. 
 *        También se guarda el largo de la lista.
 */
typedef struct lista{
	NodoNumeros* primero;
	NodoNumeros* ultimo;
	int largo;
}ListaNumeros;

/**
 * @struct Jugador
 * @brief Jugador permite guardar un nombre, un mazo inicial de 12 cartas, y dos listas enlazadas. Una de las listas
 *        permite almacenar la mano del jugador, mientras que la otra lista permite almacenar los pares eliminados por el jugador
 *		  a lo largo de toda la partida.
 */
typedef struct jugador{
	char* nombre;
	int mazoInicial[12];
	ListaNumeros* mazoLimpio;
	ListaNumeros* cartasDesechadas;
}Jugador;