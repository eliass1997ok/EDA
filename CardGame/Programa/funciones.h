/*################## IMPORTACIONES ##################*/

#include "estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/* 
 * Se crea una macro con el fin de limpiar la pantalla.
 */
#ifdef __unix__
 #define LIMPIA "clear"
#endif
#ifdef __WIN32__
 #define LIMPIA "cls"
#endif

/**
 * @brief inicializadorLista permite establecer los punteros de inicio y final de la lista a NULL, junto con un largo de 0.
 * @param lista corresponde a una lista enlazada vacía capaz de contener nodos con números.
 */
void inicializadorLista(ListaNumeros* lista);

/**
 * @brief buscarEnArreglo permite determinar si un número se encuentra dentro de un arreglo.
 * @param numero corresponde al número buscado dentro del arreglo.
 * @param arreglo corresponde a un arreglo de números dentro del cual se va a buscar el número.
 * @param largo corresponde a el largo del arreglo, esto para establecer los límites de búsqueda.
 *
 * @return 1 si el número se encuentra en el arreglo, 0 en caso contrario.
 */
int buscarEnArreglo(int numero, int* arreglo, int largo);

/**
 * @brief revolverMazo permite revolver un arreglo de cartas.
 * @param mazo corresponde a un arreglo de números. Es este arreglo el que se revolverá.
 * @param mazoRevuelto corresponde a un arreglo inicialmente vacío. Este se rellenará con los elementos de mazo, de forma aleatoria.
 * @param numero corresponde al largo del arreglo, esto para establecer los límites en los que se rellenarán las posiciones.
 */
void revolverMazo(int* mazo, int* mazoRevuelto, int numero);

/**
 * @brief freeNumeros permite liberar la memoria ocupada en una lista enlazada de números.
 * @param nodo corresponde a un puntero hacia un nodo de una lista enlazada. Se liberará la memoria a partir de este nodo en la lista.
 */
void freeNumeros(NodoNumeros* nodo);

/**
 * @brief asignarUltimo permite volver a establecer un puntero hacia el último elemento de una lista enlazada.
 * @param lista corresponde a un puntero hacia una lista enlazada.
 */
void asignarUltimo(ListaNumeros* lista);

/**
 * @brief removerPosicion permite eliminar un nodo de una lista a partir de una posicion entregada.
 * @param lista corresponde a un puntero hacia una lista enlazada, a la cual se le eliminará un nodo.
 * @param posicion corresponde a la posición del nodo a eliminar dentro de la lista.
 */
void removerPosicion(ListaNumeros* lista, int posicion);

/**
* @brief eliminarPrimero permite eliminar el primero nodo de una lista enlazada de números.
* @param lista corresponde a un puntero hacia una lista enlazada de números, a la cual se le eliminará el primer nodo.
*/
void eliminarPrimero(ListaNumeros* lista);

/**
 * @brief appendNumero permite agregar un número a una lista enlazada.
 * @param lista corresponde a un puntero hacia una lista enlazada.
 * @param numero corresponde a el número que se agregará a la lista.
 */
void appendNumero(ListaNumeros* lista, int numero);

/**
 * @brief obtenerNumeroPorPosicion permite obtener un número de una lista enlazada a partir de una posición.
 * @param lista corresponde a un puntero hacia una lista enlazada.
 * @param posicion corresponde a la posición de la cual se desea obtener el número.
 * @return se retorna el número contenido en la posicion buscada de la lista.
 */

int obtenerNumeroPorPosicion(ListaNumeros* lista, int posicion);

/**
 * @brief vaciarLista permite recibir un jugador, y vaciar su mano (vacía la lista enlazada que contiene las cartas de su mano).
 * @param player corresponde a un puntero hacia una estructura jugador. Se vaciará la lista enlazada que contiene las cartas de su mano.
 */
void vaciarLista(Jugador* player);

/**
 * @brief limpiarRepeticionesLista permite recibir un jugador y eliminar las cartas repetidas de su mano.
 * @param player corresponde a un puntero a un jugador, al cual se le revisará su mano y se le eliminarán los pares. (Se borran de una lista enlazada).
 * @param nombre corresponde a un string, el cual servirá para comprobar que el usuario sea "JANICE". Esto permitirá mostrar los pares eliminados.
 */
void limpiarRepeticionesLista(Jugador* player, char* nombre);

/**
 * @brief limpiarRepeticiones permite eliminar las repeticiones dentro de un arreglo inicial de 12 cartas (las repartidas al jugador).
 * @param player corresponde a un puntero hacia un jugador, al cual se le eliminarán los pares de las cartas repartidas inicialmente.
 */
void limpiarRepeticiones(Jugador* player);

/**
 * @brief desordenarLista permite desordenar los elementos de una lista enlazada.
 * @param lista corresponde a un puntero hacia una lista enlazada de números, la cual se desordenará.
 */
void desordenarLista(ListaNumeros* lista);

/**
 * @brief contarCartasEnJuego permite determinar la cantidad de cartas que hay en juego. Esto para determinar en qué momento ya hay un perdedor.
 * @param arreglo corresponde a un arreglo de punteros a jugador, estos punteros van hacia cada jugador, esté o no eliminado.
 * @param cantidadJugadores corresponde a un número que indica la cantidad de jugadores que hay, estén o no eliminados. 
 *        Esto para establecer los límites del arreglo.
 */
int contarCartasEnJuego(Jugador** arreglo, int cantidadJugadores);

/**
 * @brief revolverManoJugador permite recibir a un jugador y revolver su mano actual de cartas.
 * @param player corresponde a un puntero hacia un jugador. Es a este jugador al cual se le revolverán las cartas.
 * @param nombre corresponde a un string, el cual servirá para comprobar que el usuario sea "JANICE".
 *        Esto permitirá mostrar la mano del jugador una vez revuelta.
*/
void revolverManoJugador(Jugador* player, char* nombre);

/**
 * @brief comenzarJuego permite llamar a las funciones anteriores, siguiendo la lógica del poto sucio.
 */
void comenzarJuego();