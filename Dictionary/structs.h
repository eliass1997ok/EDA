#pragma once

//######################        IMPORTACIONES       ######################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//###################### DEFINICION DE ESTRUCTURAS ######################


/**
 * @struct Node
 * @brief Node corresponde a la estructura que permite generar un árbol. Cada nodo contiene los siguientes elementos:
 * 		  spanishWord: palabra en español dentro del árbol.
 * 		  anotherLanguageWord: palabra en otro idioma dentro del árbol.
 * 		  spanishMeaning: significado de la palabra en español.
 * 		  spanishFather: puntero al padre del nodo, en la representación en español.
 * 		  anotherLanguageFather: puntero al padre del nodo, en la representación en otro idioma.
 * 		  spanishLeftSon: puntero al hijo izquierdo del nodo, en la representación en español.
 * 		  spanishRightSon: puntero al hijo derecho del nodo, en la representación en español.
 * 		  anotherLanguageLeftSon: puntero al hijo izquierdo del nodo, en la representación en otro idioma.
 * 		  anotherLanguageRightSon: puntero al hijo derecho del nodo, en la representación en otro idioma.
 */
typedef struct node{
	char* spanishWord;
	char* anotherLanguageWord;
	char* spanishMeaning;
	struct node* spanishFather;
	struct node* anotherLanguageFather;
	struct node* spanishLeftSon;
	struct node* spanishRightSon;
	struct node* anotherLanguageLeftSon;
	struct node* anotherLanguageRightSon;
}Node;

/**
 * @struct Tree
 * @brief Tree corresponde a la estructura que permite acceder a los nodos del árbol. Esta estructura contiene
 * 		  dos punteros que permiten acceder al árbol en distintas posiciones, siendo estas, las raíces tanto para
 * 		  el español como para el inglés.
 * 		  spanishRoot: puntero al nodo raíz de la representación en español.
 * 		  anotherLanguageRoot: puntero al nodo raíz de la representación en otro idioma.		  
 */
typedef struct tree{
	Node* spanishRoot;
	Node* anotherLanguageRoot;
}Tree;

/**
 * @struct Words
 * @brief Words corresponde al nodo de una lista enlazada. Permite almacenar los siguiente datos:
 * 		  spanishWord: palabra en español.
 * 		  anotherLanguageWord: palabra en otro idioma.
 * 		  spanishMeaning: significado de la palabra en español.
 * 		  nextWord: puntero a una estructura del mismo tipo.
 */
typedef struct words{
	char* spanishWord;
	char* anotherLanguageWord;
	char* spanishMeaning;
	struct words* nextWord;
}Words;

/**
 * @struct List
 * @brief List corresponde a la estructura que permite acceder al primer y último nodo de una lista enlazada. 
 *        También se guarda el largo de la lista.
 * 		  first: puntero al primer nodo de la lista enlazada.
 * 		  last: puntero al último nodo de la lista enlazada.
 * 		  length: largo de la lista enlazada.
 */
typedef struct list{
	Words* first;
	Words* last;
	int length;
}List;