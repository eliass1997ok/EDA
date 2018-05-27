#include "funciones.h"
#include "estructuras.h"

void inicializadorLista(ListaNumeros* lista){
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->largo = 0;
}

int buscarEnArreglo(int numero, int* arreglo, int largo){
	for(int i=0; i<largo; i++){
		if(arreglo[i] == numero){
			return 1;
		}
	}
	return 0;
}

void revolverMazo(int* mazo, int* mazoRevuelto, int numero){
	int posicionesOcupadas[numero];

	for(int i=0; i<numero; i++){
		posicionesOcupadas[i] = -1;
	}

	int posicionCerrada = 0;
	srand(time(NULL));

	while(posicionCerrada<numero){
		int posicion = rand()%numero;
		int busquedaValor = buscarEnArreglo(posicion, posicionesOcupadas, numero);

		if(busquedaValor == 0){
			mazoRevuelto[posicionCerrada] = mazo[posicion];
			posicionesOcupadas[posicionCerrada] = posicion;
			posicionCerrada++;
		}
	}
}

void freeNumeros(NodoNumeros* nodo){
	NodoNumeros* tmp;
	while(nodo != NULL){
		tmp = nodo;
		nodo = nodo->siguiente;
		free(tmp);
	}
}

void asignarUltimo(ListaNumeros* lista){
	NodoNumeros* aux;
	aux = lista->primero;
	while(aux->siguiente != NULL){
		aux = aux->siguiente;
	}
	lista->ultimo = aux;
}

void removerPosicion(ListaNumeros* lista, int posicion){
	if(lista->primero == NULL){
		return;
	}

	NodoNumeros* aux = lista->primero;
 
	if(posicion == 0){
		lista->primero = aux->siguiente;
		free(aux);  
		lista->largo--;
		return;
    }

	for(int i=0; aux!=NULL && i<posicion-1; i++){
		aux = aux->siguiente;
	}

    if(aux == NULL || aux->siguiente == NULL){
         return;
 	}

	NodoNumeros* next = aux->siguiente->siguiente;
	free(aux->siguiente);
	lista->largo--; 
	aux->siguiente = next;
}

void eliminarPrimero(ListaNumeros* lista){
	NodoNumeros* aux;
	aux = lista->primero;
	lista->primero = lista->primero->siguiente;
	free(aux);
	lista->largo--;
}

void appendNumero(ListaNumeros* lista, int numero){
	NodoNumeros* nodo;
	nodo = (NodoNumeros*)calloc(1, sizeof(NodoNumeros));

	nodo->numero = numero;
	nodo->siguiente = NULL;

	if(lista->largo == 0){
		lista->primero = nodo;
		lista->ultimo = nodo;
	}
	else{
		lista->ultimo->siguiente = nodo;
		lista->ultimo = nodo;
	}
	lista->largo++;
}

int obtenerNumeroPorPosicion(ListaNumeros* lista, int posicion){
	int i = 0;
	NodoNumeros* aux;
	aux = lista->primero;

	while(aux!=NULL){
		if(i==posicion){
			return aux->numero;
		}
		else{
			aux = aux->siguiente;
			i++;
		}
	}
	return 0;
}

void vaciarLista(Jugador* player){
	while(player->mazoLimpio->largo > 0){
		eliminarPrimero(player->mazoLimpio);
	}
}

void limpiarRepeticionesLista(Jugador* player, char* nombre){
	int cantidadElementos = player->mazoLimpio->largo;
	int cartas[cantidadElementos];
	int repetidos[cantidadElementos];

	for(int i=0; i<cantidadElementos; i++){
		repetidos[i] = -1;
		cartas[i] = obtenerNumeroPorPosicion(player->mazoLimpio, i);
	}

	vaciarLista(player);
	
	int k=0;
	
	for(int i=0; i<cantidadElementos; i++){
		for(int j=i+1; j<cantidadElementos; j++){
			if((cartas[i] == cartas[j]) && (buscarEnArreglo(i, repetidos, cantidadElementos)==0)){
				if(strcmp(nombre, "JANICE") == 0 || (strcmp(player->nombre, "CPU1") != 0 && strcmp(player->nombre, "CPU2") != 0 && strcmp(player->nombre, "CPU3") != 0 )){
					printf("Pares Eliminados del jugador %s tras agregar carta: %d y %d !\n\n",player->nombre, cartas[i], cartas[j]);
				}

				repetidos[k++] = j;
				repetidos[k++] = i;
				break;	
			}
		}
	}

	for(int i=0; i<cantidadElementos; i++){
		int numero = cartas[i];
		if(buscarEnArreglo(i, repetidos, cantidadElementos) == 0){
			appendNumero(player->mazoLimpio, numero);
		}
		else{
			appendNumero(player->cartasDesechadas, numero);
		}
	}
}

void limpiarRepeticiones(Jugador* player){
	int repeticiones[12];
	for(int z=0; z<12; z++){
		repeticiones[z] = -1;
	}
	int k=0;
	for(int i=0; i<12; i++){
		for(int j=i+1; j<12; j++){
			if((player->mazoInicial[i] == player->mazoInicial[j]) && (buscarEnArreglo(i, repeticiones, 12)==0)){
				repeticiones[k++] = j;
				repeticiones[k++] = i;
				break;
			}
		}
	}

	ListaNumeros* mazoLimpio;
	mazoLimpio = (ListaNumeros*)calloc(1, sizeof(ListaNumeros));
	ListaNumeros* cartasDesechadas;
	cartasDesechadas = (ListaNumeros*)calloc(1, sizeof(ListaNumeros));

	for(int k=0; k<12; k++){
		if(buscarEnArreglo(k, repeticiones, 12)==1){
			appendNumero(cartasDesechadas, player->mazoInicial[k]);
		}
		else{
			appendNumero(mazoLimpio, player->mazoInicial[k]);
		}
	}
	player->mazoLimpio = mazoLimpio;
	player->cartasDesechadas = cartasDesechadas;
}

void desordenarLista(ListaNumeros* lista){
	int largo = lista->largo;
	int numeros[largo];
	int numerosDesordenados[largo];
	int posicionesOcupadas[largo];

	for(int i=0; i<largo; i++){
		numeros[i] = obtenerNumeroPorPosicion(lista, 0);
		eliminarPrimero(lista);

		numerosDesordenados[i] = -1;
		posicionesOcupadas[i] = -1;
	}
	
	int posicionCerrada = 0;
	srand(time(NULL));

	while(posicionCerrada < largo){
		int posicion = rand()%largo;
		int busquedaValor = buscarEnArreglo(posicion, posicionesOcupadas, largo);

		if(busquedaValor == 0){
			numerosDesordenados[posicionCerrada] = numeros[posicion];
			posicionesOcupadas[posicionCerrada] = posicion;
			posicionCerrada++;
		}
	}

	for(int i=0; i<largo; i++){
		appendNumero(lista, numerosDesordenados[i]);
	}
}

int contarCartasEnJuego(Jugador** arreglo, int cantidadJugadores){
	int cartasEnJuego = 0;

	for(int i=0; i<cantidadJugadores; i++){
		cartasEnJuego = cartasEnJuego+arreglo[i]->mazoLimpio->largo;
	}

	return cartasEnJuego;
}

void revolverManoJugador(Jugador* player, char* nombre){
	int cantidadElementos = player->mazoLimpio->largo;
	int mazo[cantidadElementos];
	int mazoRevuelto[cantidadElementos];

	if(strcmp(nombre, "JANICE") == 0){
		printf("Revolviendo mano de %s...\n", player->nombre);
	}
	for(int i=0; i<cantidadElementos; i++){
		mazo[i] = -1;
	}

	for(int i=0; i<cantidadElementos; i++){
		int numero;
		numero = obtenerNumeroPorPosicion(player->mazoLimpio, i);
		mazo[i] = numero;
	}
	vaciarLista(player);

	revolverMazo(mazo, mazoRevuelto, cantidadElementos);

	if(strcmp(nombre, "JANICE") == 0){
		printf("Mano revuelta de %s:", player->nombre);
	}

	for(int i=0; i<cantidadElementos; i++){
		if(strcmp(nombre, "JANICE") == 0){
			if(i<cantidadElementos-1){
				printf(" %d,",mazoRevuelto[i]);	
			}
			else{
				printf(" %d\n", mazoRevuelto[i]);
			}
			
		}
		appendNumero(player->mazoLimpio, mazoRevuelto[i]);
	}	
}

void comenzarJuego(){
	int mazo[53] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14};
	int mazoRevuelto[53];
	revolverMazo(mazo, mazoRevuelto, 53);
	char nombre[30];
	int tipoJugador;
	printf("Ingrese su nombre de jugador: ");
	scanf("%[^\n]s", nombre);
	int jugadores;
	printf("Bienvenido, %s, ¿contra cuántos jugadores desea jugar?: ", nombre);
	scanf("%d", &jugadores);
	getchar();

	while(jugadores<1 || jugadores>3){
		printf("Lamentablemente, el juego sólo soporta desde 1 hasta 3 rivales. Vuelva a ingresar un número, esta vez entre 1 y 3\n");
		printf("¿Contra cuántos jugadores desea jugar?: ");
		scanf("%d", &jugadores);
		getchar();
	}
	if(jugadores == 1){
		printf("¿Contra que computadora desea jugar?\n");
		printf("[1] CPU-1\n");
		printf("[2] CPU-2\n");
		printf("[3] CPU-3\n");
		printf("Ingrese una opción: ");
		scanf("%d", &tipoJugador);
		getchar();

		while(tipoJugador < 1 || tipoJugador > 3){
			printf("Ha ingresado una opción no válida.\n");
			printf("¿Contra que computadora desea jugar?\n");
			printf("[1] CPU-1\n");
			printf("[2] CPU-2\n");
			printf("[3] CPU-3\n");
			printf("Ingrese una opción: ");
			scanf("%d", &tipoJugador);
			getchar();
		}
	}

	jugadores++;
	
	int j=0;
	Jugador* players[jugadores];
	system(LIMPIA);
	for(int i=0; i<jugadores; i++){
		Jugador* player;
		player = (Jugador*)calloc(1, sizeof(Jugador));
		player->nombre = (char*)calloc(30, sizeof(char));
		
		if(jugadores == 2){
			if(i==0){
				strcpy(player->nombre, nombre);
			}
			if(tipoJugador == 1 && i==1){
				strcpy(player->nombre, "CPU1");
			}
			if(tipoJugador == 2 && i==1){
				strcpy(player->nombre, "CPU2");
			}
			if(tipoJugador == 3 && i==1){
				strcpy(player->nombre, "CPU3");
			}
			int aux = 0;

			for(j; aux<12; aux++){
				player->mazoInicial[aux] = mazoRevuelto[j];
				j++;
			}
			players[i] = player;
		}
		else{
			if(i==0){
				strcpy(player->nombre, nombre);
			}
			else if(i==1){
				strcpy(player->nombre, "CPU1");
			}
			else if(i==2){
				strcpy(player->nombre, "CPU2");
			}
			else{
				strcpy(player->nombre, "CPU3");
			}
			int aux = 0;
			int a=0;
			for(j; aux<12; aux++){
				player->mazoInicial[aux] = mazoRevuelto[j];
				j++;
			}
			players[i] = player;
		}			
	}

	ListaNumeros* mazoRestante;
	mazoRestante = (ListaNumeros*)calloc(1, sizeof(ListaNumeros));
	inicializadorLista(mazoRestante);
	for(j; j<53; j++){
		appendNumero(mazoRestante, mazoRevuelto[j]);
	}

	for(int k=0; k<jugadores; k++){
		
		if((strcmp(players[0]->nombre, "JANICE")==0 || (strcmp(players[k]->nombre, "CPU1") != 0 && strcmp(players[k]->nombre, "CPU2") != 0 && strcmp(players[k]->nombre, "CPU3") != 0 ))){
			printf("Nombre: %s\n", players[k]->nombre);
			printf("Mazo Inicial de %s:", players[k]->nombre);
			for(int i=0; i<12; i++){
				if(i<11){
					printf(" %d,", players[k]->mazoInicial[i]);	
				}
				else{
					printf(" %d\n\n", players[k]->mazoInicial[i]);
				}
			}	
		}

		limpiarRepeticiones(players[k]);
		if((strcmp(players[0]->nombre, "JANICE")==0)){
			NodoNumeros* aux2;
			aux2 = players[k]->cartasDesechadas->primero;
			printf("\n");
			if(strcmp(players[0]->nombre, "JANICE")==0){
				printf("######## ETAPA 1 DEL JUEGO ########\n");
			}
			
			printf("\n");
			printf("Pares Desechados por %s:",players[k]->nombre);
			while(aux2!=NULL){
				if(aux2->siguiente != NULL){
					printf(" %d,", aux2->numero);
				}
				else{
					printf(" %d\n", aux2->numero);	
				}
				
				aux2 = aux2->siguiente;
			}

			NodoNumeros* aux;
			aux = players[k]->mazoLimpio->primero;
			printf("Cartas en mano tras descartar pares de %s:", players[k]->nombre);
			while(aux!=NULL){
				if(aux->siguiente != NULL){
					printf(" %d,", aux->numero);	
				}
				else{
					printf(" %d\n", aux->numero);	
				}
				aux = aux->siguiente;
			}
			
			free(aux);
			free(aux2);
			printf("\n");
		}

	}
	if(strcmp(players[0]->nombre, "JANICE") == 0){
		NodoNumeros* aux;
		aux = mazoRestante->primero;
		printf("Cartas restantes en el mazo:");
		while(aux!=NULL){
			if(aux->siguiente != NULL){
				printf(" %d,", aux->numero);	
			}
			else{
				printf(" %d\n", aux->numero);
			}
			
			aux = aux->siguiente;
		}
		printf("\n");
		free(aux);		
	}

	int k=0;
	while(k<jugadores){
		while(mazoRestante->largo != 0){
			if(strcmp(players[0]->nombre, "JANICE") == 0){
				printf("A %s se le agregó la siguiente carta: %d\n", players[k]->nombre, mazoRestante->primero->numero);
				appendNumero(players[k]->mazoLimpio, mazoRestante->primero->numero);
				eliminarPrimero(mazoRestante);
				k++;
				if(k==jugadores){
					break;
				}
			}
			else{
				if(k==0){
					appendNumero(players[k]->mazoLimpio, mazoRestante->primero->numero);
					eliminarPrimero(mazoRestante);
					k++;
					
				}
				else{
					appendNumero(players[k]->mazoLimpio, mazoRestante->primero->numero);
					eliminarPrimero(mazoRestante);
					k++;
					if(k==jugadores){
						break;
					}
				}
			}

		}
		if(mazoRestante->largo != 0){
			k=0;
		}
		else{
			break;
		}
		
	}

	if(strcmp(players[0]->nombre, "JANICE") == 0){
		printf("\n");
		printf("######## ETAPA 2 DEL JUEGO ########\n\n");		
	}

	for(int z=0; z<jugadores; z++){
		limpiarRepeticionesLista(players[z], players[0]->nombre);
		asignarUltimo(players[z]->mazoLimpio);
	}


	int cartasEnJuego = contarCartasEnJuego(players, jugadores); 

	if(strcmp(players[0]->nombre, "JANICE") == 0){
		printf("\n");
		printf("######## ETAPA 3 DEL JUEGO ########\n");
	}

	while(cartasEnJuego > 1){
		for(int i=0; i<jugadores; i++){
			if(players[i]->mazoLimpio->largo > 0){
				int j;
				int posicion;
				int carta;
				j = i+1;
				if(j>=jugadores){
					j=0;
				}
				while(players[j]->mazoLimpio->largo < 1){
					j++;
					if(j>=jugadores){
						j=0;
					}	
				}
				if(j!=i){
					if(((strcmp(players[i]->nombre, "CPU1")!=0 && strcmp(players[i]->nombre, "CPU2")!=0 && strcmp(players[i]->nombre, "CPU3")!=0) || 
						strcmp(players[0]->nombre, "JANICE") == 0) || (strcmp(players[j]->nombre, "CPU1")!=0 && strcmp(players[j]->nombre, "CPU2")!=0 && strcmp(players[j]->nombre, "CPU3")!=0)){
						printf("\n");						
						printf("%s le pide cartas a %s, quien posee %d cartas.\n", players[i]->nombre, players[j]->nombre, players[j]->mazoLimpio->largo);
						printf("\n");

						if((strcmp(players[i]->nombre, "CPU1") != 0 && strcmp(players[i]->nombre, "CPU2") != 0 && strcmp(players[i]->nombre, "CPU3") != 0) || (strcmp(players[0]->nombre, "JANICE")==0)){
							NodoNumeros* nodo1;
							nodo1 = players[i]->mazoLimpio->primero;

							printf("Cartas de %s:", players[i]->nombre);
							while(nodo1!=NULL){
								if(nodo1->siguiente != NULL){
									printf(" %d,", nodo1->numero);	
								}
								else{
									printf(" %d\n", nodo1->numero);	
								}
								
								nodo1 = nodo1->siguiente;
							}
						}

						if(strcmp(players[0]->nombre, "JANICE") == 0 ){
							NodoNumeros* nodo2;
							nodo2 = players[j]->mazoLimpio->primero;
							printf("Cartas de %s: ", players[j]->nombre);
							while(nodo2!=NULL){
								if(nodo2->siguiente != NULL){
									printf(" %d,", nodo2->numero);	
								}
								else{
									printf(" %d\n", nodo2->numero);	
								}
								
								nodo2 = nodo2->siguiente;
							}	
						}
						else if((strcmp(players[j]->nombre, "CPU1") == 0 || strcmp(players[j]->nombre, "CPU2") == 0 || strcmp(players[j]->nombre, "CPU3") == 0)){
							int cantidadCartas = players[j]->mazoLimpio->largo;
							printf("Cartas de %s:", players[j]->nombre);
							for(int i=1; i<=cantidadCartas; i++){
								if(i<cantidadCartas){
									printf("[  %d  ] ", i);
								}
								else{
									printf("[  %d  ] \n", i);	
								}
							}
						}
					}

					if(strcmp(players[j]->nombre, "CPU1")!=0 && strcmp(players[j]->nombre, "CPU2")!=0 && strcmp(players[j]->nombre, "CPU3")!=0){
						int respuesta;
						printf("¿Desea revolver su mano antes de que le quiten una carta?\n");
						printf("[ 1 ] Sí\n" );
						printf("[ 2 ] No\n" );
						printf("\n");
						printf("Ingrese su opción: ");
						scanf("%d", &respuesta);
						getchar();

						while(respuesta<1 || respuesta>2){
							printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
							printf("¿Desea revolver su mano antes de que le quiten una carta?\n");
							printf("[ 1 ] Sí\n" );
							printf("[ 2 ] No\n" );
							printf("\n");
							printf("Ingrese su opción: ");
							scanf("%d", &respuesta);
							getchar();
						}

						if(respuesta == 1){
							if(strcmp(players[j]->nombre, "JANICE") != 0){
								printf("Revolviendo mano...\n");
							}
							revolverManoJugador(players[j], players[0]->nombre);
						}
					}
					if(strcmp(players[j]->nombre, "CPU2")==0){

						revolverManoJugador(players[j], players[0]->nombre);
					}
					if(strcmp(players[i]->nombre, "CPU1")!=0 && strcmp(players[i]->nombre, "CPU2")!=0 && strcmp(players[i]->nombre, "CPU3")!=0){
						printf("Ingrese una carta que le quiera pedir a %s (debe estar entre 1 y %d): ",players[j]->nombre, players[j]->mazoLimpio->largo);
						scanf("%d", &posicion);
						getchar();
						while(posicion<1 || posicion>players[j]->mazoLimpio->largo){
							printf("Ha ingresado una carta no válida. Por favor, vuelva a ingresar una carta, esta debe estar entre 1 y %d: \n", players[j]->mazoLimpio->largo);
							scanf("%d", &posicion);
							getchar();
						}	
					}
					if(strcmp(players[i]->nombre, "CPU1")==0){
						posicion = 1;
					}
					else if(strcmp(players[i]->nombre, "CPU2")==0){
						posicion = players[j]->mazoLimpio->largo;
					}
					else if(strcmp(players[i]->nombre, "CPU3")==0){
						srand(time(NULL));

						posicion = (rand()%((players[j]->mazoLimpio->largo)))+1;
					}

					carta = obtenerNumeroPorPosicion(players[j]->mazoLimpio, posicion-1);

					if((strcmp(players[i]->nombre, "CPU1") != 0 && strcmp(players[i]->nombre, "CPU2") != 0 && strcmp(players[i]->nombre, "CPU3") != 0) 
						|| (strcmp(players[0]->nombre, "JANICE")==0)
						|| (strcmp(players[j]->nombre, "CPU1") != 0 && strcmp(players[j]->nombre, "CPU2") != 0 && strcmp(players[j]->nombre, "CPU3") != 0)){
						printf("\n");
						printf("Carta Robada por %s a %s: %d\n", players[i]->nombre, players[j]->nombre, carta);
						printf("\n");
					}
					appendNumero(players[i]->mazoLimpio, carta);

					limpiarRepeticionesLista(players[i], players[0]->nombre);

					removerPosicion(players[j]->mazoLimpio, posicion-1);

					if(players[j]->mazoLimpio->largo >=1){
						asignarUltimo(players[j]->mazoLimpio);
					}
					if(strcmp(players[0]->nombre, "JANICE") == 0){
						printf("Presione [ENTER] para ver la siguiente jugada.\n");
						getchar();
					}

					cartasEnJuego = contarCartasEnJuego(players, jugadores);
				}
			}
		}

		cartasEnJuego = contarCartasEnJuego(players, jugadores);
	}

	for(int i=0; i< jugadores; i++){
		if(players[i]->mazoLimpio->largo != 0){
			printf("¡%s tiene el poto sucio!\n", players[i]->nombre);
			printf("Presione [ENTER] para cerrar el programa.");
			getchar();
		}
	}

	for(int i=0; i<jugadores; i++){
		freeNumeros(players[i]->mazoLimpio->primero);
		freeNumeros(players[i]->cartasDesechadas->primero);
		free(players[i]->nombre);
		free(players[i]);
	}

	freeNumeros(mazoRestante->primero);
}