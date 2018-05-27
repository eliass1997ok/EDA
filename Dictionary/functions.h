#pragma once

#include "structs.h"

/**
 * @brief initializeList permite establecer los punteros de inicio y final de la lista a NULL, junto con un largo de 0.
 * @param list corresponde a una lista enlazada vacía capaz de contener nodos con palabras y frases.
 * t(n) = 3
 * o(n) = c
 */
void initializeList(List* list);

/**
 * @brief freeList permite liberar la memoria ocupada en una lista enlazada.
 * @param words corresponde a un puntero hacia un nodo de una lista enlazada. 
 * 		  Se liberará la memoria a partir de este nodo en la lista.
 * t(n) = 6n
 * o(n) = n
 */
void freeList(Words* words);

/**
 * @brief clearScreen corresponde a una macro que permite limpiar la terminal del usuario.
 * t(n) = 1
 * o(n) = c
 *
 */
void clearScreen();

/**
 * @brief createNodes permite "transformar" los elementos de la lista enlazada en nodos para el árbol AVL. 
 * @param list corresponde a la lista enlazada que contiene los elementos a transformar.
 *
 * @return Node** se retorna un arreglo con los nodos que deben ser insertados en el árbol AVL.
 * t(n) = 28n+3
 * o(n) = n
 */
Node** createNodes(List* list);

/**
 * @brief alphabetPosition permite determinar la posición de una letra dentro del alfabeto.
 * @param letter corresponde al caracter buscado.
 *
 * @return int corresponde a la posición que toma el caracter dentro del alfabeto.
 * t(n) = n+1
 * o(n) = n
 */
int alphabetPosition(char letter);

/**
 * @brief wordsCompare permite determinar entre dos palabras, cual debiese estar antes y cual debiese estar después
 * 		  en el alfabeto.
 * @param firstWord corresponde a una de las palabras.
 * @param secondWords corresponde a una de las palabras.
 *
 * @return int se retorna un entero que permite identificar cuál de las palabras va antes y cual después.
 * t(n) = 2n+2
 * o(n) = n
 */
int wordsCompare(char* firstWord, char* secondWord);

/**
 * @brief appendWord permite agregar nodos a la lista enlazada.
 * @param list corresponde a la lista enlazada.
 * @param spanishWord corresponde a la palabra representativa del español.
 * @param anotherLanguageWord corresponde a la palabra traducción de spanishWord.
 * @param spanishMeaning corresponde a la definición de la palabra en español.
 * t(n) = 11
 * o(n) = c
 */
void appendWord(List* list, char* spanishWord, char* anotherLanguageWord, char* spanishMeaning);

/**
 * @brief readFile permite leer un archivo de texto que lleva por nombre "Diccionario.in". Se genera una 
 * 		  lista enlazada con el contenido, con la información ordenada.
 * 
 * @return List* se retorna una lista enlazada con la información del archivo.
 * t(n) = 24n+5
 * o(n) = n
 */
List* readFile();

/**
 * @brief heigthSpanishNode permite determinar la altura de un nodo, en ĺa representación en español del árbol AVL.
 * @param node corresponde al nodo desde el cual se desea determinar la altura.
 *
 * @return int corresponde a la altura del nodo.
 * t(n) = t(n/2) + 4
 * o(n) = log(n)
 */
int heightSpanishNode(Node* node);

/**
 * @brief heigthAnotherLanguageNode permite determinar la altura de un nodo, en ĺa representación en 
 * 		  otro idioma del árbol AVL.
 * @param node corresponde al nodo desde el cual se desea determinar la altura.
 *
 * @return int corresponde a la altura del nodo.
 * t(n) = t(n/2) + 4
 * o(n) = log(n)
 *
 */
int heightAnotherLanguageNode(Node* node);

/**
 * @brief differenceBetweenHeightInSpanish permite determinar la diferencia de alturas entre los 
 * 		  sub-árboles de un nodo, en ĺa representación en español del árbol AVL.
 * @param node corresponde al nodo desde el cual se desea determinar la diferencia de alturas.
 *
 * @return int corresponde a la diferencia de alturas del nodo.
 * t(n) = t(n/2)+1
 * o(n) = log(n)
 */
int differenceBetweenHeightInSpanish(Node* node);

/**
 * @brief differenceBetweenHeightInAnotherLanguage permite determinar la diferencia de alturas entre los 
 * 		  sub-árboles de un nodo, en ĺa representación en otro idioma del árbol AVL.
 * @param node corresponde al nodo desde el cual se desea determinar la diferencia de alturas.
 *
 * @return int corresponde a la diferencia de alturas del nodo.
 *
 * t(n) = t(n/2)+1
 * o(n) = log(n)
 */
int differenceBetweenHeightInAnotherLanguage(Node* node);

/**
 * @brief rotateLeftSpanishTree permite rotar hacia la izquierda un trío de nodos, en ĺa 
 * 		  representación en español del árbol AVL.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param node corresponde al nodo desde donde se hace la rotación.
 *
 * t(n) = 7
 * o(n) = c
 */
void rotateLeftSpanishTree(Tree* tree, Node* node);

/**
 * @brief rotateLeftAnotherLanguageTree permite rotar hacia la izquierda un trío de nodos, en ĺa 
 * 		  representación en otro idioma del árbol AVL.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param node corresponde al nodo desde donde se hace la rotación.
 *
 * t(n) = 7
 * o(n) = c
 */
void rotateLeftAnotherLanguageTree(Tree* tree, Node* node);

/**
 * @brief rotateRightSpanishTree permite rotar hacia la derecha un trío de nodos, en ĺa 
 * 		  representación en español del árbol AVL.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param node corresponde al nodo desde donde se hace la rotación.
 *
 * t(n) = 7
 * o(n) = c
 */
void rotateRightSpanishTree(Tree* tree, Node* node);

/**
 * @brief rotateRightAnotherLanguageTree permite rotar hacia la derecha un trío de nodos, en ĺa 
 * 		  representación en otro idioma del árbol AVL.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param node corresponde al nodo desde donde se hace la rotación.
 *
 * t(n) = 7
 * o(n) = c
 */
void rotateRightAnotherLanguageTree(Tree* tree, Node* node);

/**
 * @brief balanceSpanishTree permite transformar un árbol binario ordenado en AVL, en su representación en español.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param node corresponde al nodo desde donde se determina el balanceo del árbol.
 *
 * t(n) = 2log(n)+12
 * o(n) = log(n)
 */
void balanceSpanishTree(Tree* tree, Node* node);

/**
 * @brief balanceAnotherLanguageTree permite transformar un árbol binario ordenado 
 * 		  en AVL, en su representación en otro idioma.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param node corresponde al nodo desde donde se determina el balanceo del árbol.
 *
 * t(n) = 2log(n)+12
 * o(n) = log(n)
 */
void balanceAnotherLanguageTree(Tree* tree, Node* node);

/**
 * @brief insertAnotherLanguageTree permite insertar un nodo dentro del árbol, manteniendo el carácter de 
 * 		  AVL para la representación en otro idioma.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param nodeToInsert corresponde al nodo que se inserta en el árbol
 *
 * t(n) = 15nlog(n)+n+1
 * o(n) = nlog(n)
 */
void insertAnotherLanguageTree(Tree* tree, Node* nodeToInsert);

/**
 * @brief insertSpanishTree permite insertar un nodo dentro del árbol, manteniendo el carácter de 
 * 		  AVL para la representación en español.
 * @param tree corresponde al árbol que representa al diccionario.
 * @param nodeToInsert corresponde al nodo que se inserta en el árbol.
 *
 * t(n) = 15nlog(n)+n+1
 * o(n) = nlog(n)
 */
void insertSpanishInTree(Tree* tree, Node* nodeToInsert);

/**
 * @brief inOrderSpanish permite escribir dentro de un archivo de texto llamado "Solution.out" el contenido de un 
 * 		  nodo en específico. Este se escribe en un formato especial para la representación en español.
 * @param node corresponde al nodo del árbol al que se accede para escribir el archivo.
 * @param f corresponde al archivo al cual se le escribe el contenido deĺ nodo.
 *
 * t(n) = 2t(n/2) + 11
 * o(n) = n
 */
void inOrderSpanish(Node* node, FILE* f);

/**
 * @brief inOrderAnotherLanguage permite escribir dentro de un archivo de texto llamado "Solution.out" el contenido 
 * 		  de un nodo en específico. Esto se escribe con un formato especial para la representación en otro idioma.
 * @param node corresponde al nodo del árbol al que se accede para escribir el archivo.
 * @param f corresponde al archivo al cual se le escribe el contenido deĺ nodo.
 *
 * t(n) = 2t(n/2) + 11
 * o(n) = n
 */
void inOrderAnotherLanguage(Node* node, FILE* f);

/**
 * @brief searchSpanishMeaning permite recorrer el árbol en búsqueda de una palabra (en español), para 
 * 		  retornar su significado en este idioma.
 * @param node corresponde al nodo del árbol desde el cual se comienza a recorrer para buscar la palabra.
 * @param wordToSearch corresponde a la palabra en español de la cual se busca el significado.
 *
 * @return char* se retorna el significado de la palabra (en caso de existir). Si no existe la palabra, se retorna
 * 		   un tipo especial de resultado.
 *
 * t(n) = t(n/2)
 * o(n) = log(n)
 */
char* searchSpanishMeaning(Node* node, char* wordToSearch);

/**
 * @brief searchAnotherLanguegeMeaning permite recorrer el árbol en búsqueda de una palabra (en otro idioma), para 
 * 		  retornar su significado en español.
 * @param node corresponde al nodo del árbol desde el cual se comienza a recorrer para buscar la palabra.
 * @param wordToSearch corresponde a la palabra en otro idioma de la cual se busca el significado.
 *
 * @return char* se retorna el significado de la palabra (en caso de existir). Si no existe la palabra, se retorna
 * 		   un tipo especial de resultado.
 *
 * t(n) = t(n/2)
 * o(n) = log(n)
 */
char* searchAnotherLanguageMeaning(Node* node, char* wordToSearch);

/**
 * @brief searchSpanishToAnotherLanguageTranslation permite recorrer el árbol en búsqueda de una  
 * 		  palabra (en español), para retornar su traducción a otro idioma.
 * @param node corresponde al nodo del árbol desde el cual se comienza a recorrer para buscar la palabra.
 * @param wordToSearch corresponde a la palabra en español de la cual se busca traducción.
 *
 * @return char* se retorna la traducción de la palabra (en caso de existir). Si no existe la palabra, se retorna
 * 		   un tipo especial de resultado.
 *
 * t(n) = t(n/2)
 * o(n) = log(n)
 */
char* searchSpanishToAnotherLanguageTranslation(Node* node, char* spanishWord);

/**
 * @brief searchAnotherLanguageToSpanishTranslation permite recorrer el árbol en búsqueda de una  
 * 		  palabra (en otro idioma), para retornar su traducción a español.
 * @param node corresponde al nodo del árbol desde el cual se comienza a recorrer para buscar la palabra.
 * @param wordToSearch corresponde a la palabra en otro idioma de la cual se busca traducción.
 *
 * @return char* se retorna la traducción de la palabra (en caso de existir). Si no existe la palabra, se retorna
 * 		   un tipo especial de resultado.
 *
 * t(n) = t(n/2)
 * o(n) = log(n)
 */
char* searchAnotherLanguageToSpanishTranslation(Node* node, char* anotherLanguageWord);

/**
 * @brief writeInOrderSpanishTree permite recorrer el árbol (representación en español) de forma que los resultados 
 * 		  se muestren de manera ordenada. Al momento de recorrer, los resultados son escritos en un archivo
 * 		  de texto llamado "Solution.out".
 * @param node corresponde al nodo del árbol desde el cual se comienza a recorrer para escribir el archivo de 
 * 		  forma ordenada.
 *
 * t(n) = n+3
 * o(n) = n
 */
void writeInOrderSpanishTree(Node* node);

/**
 * @brief writeInOrderAnotherLanguageTree permite recorrer el árbol (representación en otro idioma) de  
 * 		  forma que los resultados se muestren de manera ordenada. Al momento de recorrer, los resultados 
 * 		  son escritos en un archivo de texto llamado "Solution.out".
 * @param node corresponde al nodo del árbol desde el cual se comienza a recorrer para escribir el archivo de
 * 		  forma ordenada.
 *
 * t(n) = n+3
 * o(n) = n
 */
void writeInOrderAnotherLanguageTree(Node* node);

/**
 * @brief menu permite desplegar un menú donde el usuario pueda decidir qué quiere hacer con el programa.
 * @param tree corresponde al árbol AVL con el que funcionará el programa.
 *
 */
void menu(Tree* tree);

/**
 * @brief run permite iniciar el programa, llamando a las funciones anteriores.
 *52n+12+2n²log(n)
 */
void run();
