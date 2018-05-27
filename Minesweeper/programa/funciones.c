#include "funciones.h"

//Función que permite trabajar dentro del tablero sin sobrepasar sus márgenes.
int validarMargenes(int i, int j, int filas, int columnas){
	if(i<0 || j<0 || i>=filas || j>= columnas){
		return 0;
	}
	else{
		return 1;
	}
}

//Función que determina si la posicion x,y del tablero ya ha sido mostrada al usuario (si ya fue mostrada, la casilla se cierra, es decir, no se puede volver a mostrar).
int posicionAbierta(int filas, int columnas, int tableroAbierto[filas][columnas], int x, int y){
	if(tableroAbierto[x][y] == 1){
		return 0;
	}
	else if(tableroAbierto[x][y] == 2){
		return 1;
	}
	else{
		tableroAbierto[x][y] = 1;
		return 1;
	}
}

//Función recursiva que permite mostrarle ciertas casillas al usuario, las cuales contienen información acerca de las bombas cercanas.
void generarInformacion(int x, int y, int filas, int columnas, int tablero[filas][columnas], int tableroBombas[filas][columnas], int origen, int tableroPosiciones[filas][columnas]){
	if(tableroBombas[x][y] == 0){
		if(validarMargenes(x-1, y-1, filas, columnas) == 1 && tableroBombas[x-1][y-1] != 9 && origen != 4 && posicionAbierta(filas, columnas, tableroPosiciones, x-1, y-1) == 1){
			tablero[x-1][y-1] = tableroBombas[x-1][y-1];
			generarInformacion(x-1, y-1, filas, columnas, tablero, tableroBombas, 8, tableroPosiciones);
		}
		if(validarMargenes(x-1, y, filas, columnas) == 1 &&tableroBombas[x-1][y] != 9 && origen != 5 && posicionAbierta(filas, columnas, tableroPosiciones, x-1, y) == 1){
			tablero[x-1][y] = tableroBombas[x-1][y];
			generarInformacion(x-1, y, filas, columnas, tablero, tableroBombas, 1, tableroPosiciones);
		}
		if(validarMargenes(x-1, y+1, filas, columnas) == 1 &&tableroBombas[x-1][y+1] != 9 && origen != 6 && posicionAbierta(filas, columnas, tableroPosiciones, x-1, y+1) == 1){
			tablero[x-1][y+1] = tableroBombas[x-1][y+1];
			generarInformacion(x-1, y+1, filas, columnas, tablero, tableroBombas, 2, tableroPosiciones);
		}
		if(validarMargenes(x, y-1, filas, columnas) == 1 &&tableroBombas[x][y-1] != 9 && origen != 3 && posicionAbierta(filas, columnas, tableroPosiciones, x, y-1) == 1){
			tablero[x][y-1] = tableroBombas[x][y-1];
			generarInformacion(x, y-1, filas, columnas, tablero, tableroBombas, 7, tableroPosiciones);
		}
		if(validarMargenes(x, y+1, filas, columnas) == 1 &&tableroBombas[x][y+1] != 9 && origen != 7 && posicionAbierta(filas, columnas, tableroPosiciones, x, y+1) == 1){
			tablero[x][y+1] = tableroBombas[x][y+1];
			generarInformacion(x, y+1, filas, columnas, tablero, tableroBombas, 3, tableroPosiciones);
		}
		if(validarMargenes(x+1, y-1, filas, columnas) == 1 &&tableroBombas[x+1][y-1] != 9 && origen != 2 && posicionAbierta(filas, columnas, tableroPosiciones, x+1, y-1) == 1){
			tablero[x+1][y-1] = tableroBombas[x+1][y-1];
			generarInformacion(x+1, y-1, filas, columnas, tablero, tableroBombas, 6, tableroPosiciones);
		}
		if(validarMargenes(x+1, y, filas, columnas) == 1 &&tableroBombas[x+1][y] != 9 && origen != 1 && posicionAbierta(filas, columnas, tableroPosiciones, x+1, y) == 1){
			tablero[x+1][y] = tableroBombas[x+1][y];
			generarInformacion(x+1, y, filas, columnas, tablero, tableroBombas, 5, tableroPosiciones);
		}
		if(validarMargenes(x+1, y+1, filas, columnas) == 1 &&tableroBombas[x+1][y+1] != 9 && origen != 8 && posicionAbierta(filas, columnas, tableroPosiciones, x+1, y+1) == 1){
			tablero[x+1][y+1] = tableroBombas[x+1][y+1];
			generarInformacion(x+1, y+1, filas, columnas, tablero, tableroBombas, 4, tableroPosiciones);
		}
	}
	else if(tableroBombas[x][y] != 9){
		tablero[x][y] = tableroBombas[x][y];
	}
}

//Función que permite mostrarle al usuario un tablero de forma gráfica. También determina, mediante una comparacion con el tablero de bombas, si el usuario ha perdido o sigue en juego.
void mostrarTablero(int filas, int columnas, int x, int y, char modo, int tablero[filas][columnas], int tableroBombas[filas][columnas], int inicio){
	int i, j, k;
	for(i = 0; i <= columnas -1; i++){
		if(i<10){
			printf(" %d  ", i);	
		}
		else{
			printf(" %d ", i);
		}
	}
	printf("\n");
    
	for(k = 0; k <= columnas - 1; k++){
		printf("----");
	}
	printf("\n");
	if((modo == 'O' || modo == 'o') && tablero[x][y] == -10){
		tablero[x][y] = -1;
	}
	else if((modo == 'x' || modo == 'X') && tablero[x][y] == -10){
		tablero[x][y] = -2;	
	}
	else if((modo == 'x' || modo == 'X') && tablero[x][y] == -2){
		tablero[x][y] = -10;
	}
	else{
		tablero[x][y] = tableroBombas[x][y];
	}

	if(inicio ==0){
		tablero[x][y]=-10;
	}

	for(i = 0; i <= filas -1; i++){
		for(j = 0; j <= columnas - 1; j++){
			if((tablero[i][j] == -10)){
				printf("%s ", "[ ]");
			}
			else if(tablero[i][j] == -2){
				printf("%s ", "[X]");
			}
			else if((i==x && j == y) && ((tableroBombas[x][y] == 9 && (modo == 'o' || modo == 'O')))){
				printf("%s", " B  ");
			}
			else if(tablero[i][j]==0 || tablero[i][j] == -1){
				printf("%s ", "___");
			}
			else{
				printf("[%d] ", tablero[i][j]);
			}	 
		}
		printf("| %d", i);   
		printf("\n"); 
	}
	if(tableroBombas[x][y] == 9 && (modo == 'o' || modo == 'O')){
		printf("%s\n", "Ha perdido! La posicion elegida contenía una mina, usted ha explotado :(");
		printf("%s", "Presione enter para salir." );
		getchar();
		exit(1);
	}
}

//Función recursiva que permite validar si el usuario coloca un número menor al permitido, ya sea de filas o de columnas.
int validarCantidades(int i, int j){
	int cantidadNueva;
	if(i<=1 && j==0){
		printf("%s\n", "Ha ingresado un número inválido de filas, vuelva a ingresarlo: ");
		scanf("%d", &cantidadNueva);
		getchar();
		return validarCantidades(cantidadNueva, 0);
	}
	else if(i<=1 && j==1){
		printf("%s\n", "Ha ingresado un número inválido de columnas, vuelva a ingresarlo: ");
		scanf("%d", &cantidadNueva);
		getchar();
		return validarCantidades(cantidadNueva, 1);	
	}
	else{
		return i;
	}
}

//Función recursiva que valida la jugada del usuario, permitiendo que el usuario no se salga del tablero en su jugada.
int validarJugadas(int i, int j, int filas, int columnas){
	int cantidadNueva;
	if(i>filas-1 && j==0){
		printf("Ha ingresado un número inválido de filas (debe estar entre 0 y %d), vuelva a ingresarlo: \n", filas-1);
		scanf("%d", &cantidadNueva);
		getchar();
		return validarJugadas(cantidadNueva, 0, filas, columnas);
	}
	else if(i>columnas-1 && j==1){
		printf("Ha ingresado un número inválido de columnas (debe estar entre 0 y %d), vuelva a ingresarlo: \n", columnas-1);
		scanf("%d", &cantidadNueva);
		getchar();
		return validarJugadas(cantidadNueva, 1, filas, columnas);	
	}
	else{
		return i;
	}
}

//Función que genera un tablero con bombas al azar, posterior a la primera jugada del usuario, esto con el fin de que el usuario no pierda en su primer turno.
void generarTablero(int numeroMinas, int columnas, int filas, int posicionesConBombas[filas][columnas], int x, int y){
	int bombasColocadas = 0;
	srand(time(NULL));
	int fila = 0;
	int columna = 0;
	while(bombasColocadas<numeroMinas){
    	fila =rand()%filas;
    	columna = rand()%columnas;
    	if(fila == x && columna == y){
    		posicionesConBombas[fila][columna] = 0;
    	}
    	else if(posicionesConBombas[fila][columna] == 0){
    		posicionesConBombas[fila][columna] = 9;
    		bombasColocadas++;
    	}
    	else{
    		posicionesConBombas[fila][columna] = 9;
    		
    	}
	}

	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			if(posicionesConBombas[i][j] != 9){
				posicionesConBombas[i][j] = 0;
			}
		}
	}

	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			if(posicionesConBombas[i][j] == 9){
				if(validarMargenes(i-1, j-1, filas, columnas) == 1 && posicionesConBombas[i-1][j-1] != 9){
					posicionesConBombas[i-1][j-1]++;
				}
				if(validarMargenes(i-1, j, filas, columnas) == 1 &&posicionesConBombas[i-1][j] != 9){
					posicionesConBombas[i-1][j]++;
				}
				if(validarMargenes(i-1, j+1, filas, columnas) == 1 &&posicionesConBombas[i-1][j+1] != 9){
					posicionesConBombas[i-1][j+1]++;
				}
				if(validarMargenes(i, j-1, filas, columnas) == 1 &&posicionesConBombas[i][j-1] != 9){
					posicionesConBombas[i][j-1]++;
				}
				if(validarMargenes(i, j+1, filas, columnas) == 1 &&posicionesConBombas[i][j+1] != 9){
					posicionesConBombas[i][j+1]++;
				}
				if(validarMargenes(i+1, j-1, filas, columnas) == 1 &&posicionesConBombas[i+1][j-1] != 9){
					posicionesConBombas[i+1][j-1]++;
				}
				if(validarMargenes(i+1, j, filas, columnas) == 1 &&posicionesConBombas[i+1][j] != 9){
					posicionesConBombas[i+1][j]++;
				}
				if(validarMargenes(i+1, j+1, filas, columnas) == 1 &&posicionesConBombas[i+1][j+1] != 9){
					posicionesConBombas[i+1][j+1]++;
				}
			}
		}
	}
}

//Función que escribe un archivo llamado "solucion.out", este archivo contiene toda la información acerca del juego actual.
void escribirSolucion(int filas, int columnas, int tableroBombas[filas][columnas]){
	FILE* f = fopen("solucion.out", "w");
	if(f == NULL){
		perror("solucion.out");
	}
	fprintf(f, "%s\n", "Los  números indican la cantidad de minas alrededor del bloque." );
	fprintf(f, "%s\n", "Por otro lado, las letras 'B' indican la posicion de una bomba" );
	fprintf(f, "\n");
	int i, j, k;

	for(i = 0; i <= columnas -1; i++){
		if(i<10){
			fprintf(f, " %d  ", i);	
		}
		else{
			fprintf(f, " %d ", i);
		}
	}
	fprintf(f, "\n");
    
	for(k = 0; k <= columnas - 1; k++){
		fprintf(f, "----");
	}
	fprintf(f, "\n");

	for(i = 0; i <= filas -1; i++){
		for(j = 0; j <= columnas - 1; j++){
			if((tableroBombas[i][j] == 0)){
				fprintf(f, "%s ", "___");
			}
			else if(tableroBombas[i][j] == 9){
				fprintf(f, " B  ");
			}
			else{
				fprintf(f, "[%d] ", tableroBombas[i][j]);
			}	 
		}
		fprintf(f, "| %d", i);   
		fprintf(f, "\n"); 
	}
	fclose(f);
}

//Función que permite determinar si el usuario descubrió todas las posiciones sin bombas. De cumplirse esto, el usuario ha ganado.
int validarVictoria(int filas, int columnas, int bombas, int tableroMostrar[filas][columnas], int tableroBombas[filas][columnas], int tableroPosiciones[filas][columnas]){
	int cerrados=0;
	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			if(tableroPosiciones[i][j] == 0 || tableroPosiciones[i][j] == 2){
				cerrados++;
			}
		}
	}

	if(cerrados == bombas){
		return 1;
	}

	return 0;
}

//Función recursiva que permite validar el tipo de jugada que quiere hacer el usuario. Si ingresa un caracter no valido, el programa le da una nueva oportunidad de ingresar un caracter
char validarModo(char modo){
	char letra;
	if(modo != 'O' && modo != 'o' && modo != 'x' && modo != 'X'){
		printf("%s\n", "Ha ingresado un caracter no válido. Por favor, vuelva a ingresar un caracter (O/X): ");
		scanf("%c", &letra);
		getchar();
		return validarModo(letra);
	}
	else{
		return modo;
	}
}

//Función recursiva que permite al usuario hacer su jugada.
void jugada(int filas, int columnas, int numeroMinas, int tablero[filas][columnas], int tableroMostrar[filas][columnas], int tableroPosiciones[filas][columnas]){
	char mensaje[10];
	int fila;
	int columna;
	char modo;
	char* token;
	
	printf("Ingrese la coordenada (fila columna) y el modo (X para marcar, O para descubrir): ");
	scanf("%[^\n]%*c", mensaje); 
 	token = strtok(mensaje," "); 
 	fila = atoi(token);
 	token = strtok(NULL, " ");
 	columna = atoi(token);
 	token = strtok(NULL, " ");
 	modo = token[0];
 
 	fila = validarJugadas(fila, 0, filas, columnas);
 	columna = validarJugadas(columna, 1, filas, columnas);
 	modo = validarModo(modo);
 	if(modo == 'o' || modo == 'O'){
 		generarInformacion(fila, columna, filas, columnas, tableroMostrar, tablero, -5, tableroPosiciones);
 		tableroPosiciones[fila][columna] = 1; 
 	}

 	else if((modo == 'x' || modo == 'X') && tableroPosiciones[fila][columna] == 1){
 		tableroPosiciones[fila][columna] = 1;
 	}
 	else{
 		tableroPosiciones[fila][columna] = 0;
 	}
 	system(LIMPIA);
 	mostrarTablero(filas, columnas, fila, columna, modo, tableroMostrar, tablero, 1);

 	if(validarVictoria(filas, columnas, numeroMinas, tableroMostrar, tablero, tableroPosiciones)==1){
 		printf("%s\n", "¡FELICIDADES! HAS GANADO :D");
 		printf("%s", "Presione enter para salir." );
 		getchar();
 		exit(1);
 	}
 	
 	jugada(filas, columnas, numeroMinas, tablero, tableroMostrar, tableroPosiciones);
}

//Función que permite al usuario hacer su primera jugada. Posterior a esta jugada, se genera el tablero con bombas
void primeraJugada(int filas, int columnas, int numeroMinas,int tablero[filas][columnas], int tableroMostrar[filas][columnas], int tableroPosiciones[filas][columnas]){
	char mensaje[10];
	int fila;
	int columna;
	char modo;
	char* token;
	
	printf("Ingrese la coordenada (fila columna) y el modo (X para marcar, O para descubrir): ");
	scanf("%[^\n]%*c", mensaje); 
 	token = strtok(mensaje," "); 
 	fila = atoi(token);
 	token = strtok(NULL, " ");
 	columna = atoi(token);
 	token = strtok(NULL, " ");
 	modo = token[0];

 	fila = validarJugadas(fila, 0, filas, columnas);
 	columna = validarJugadas(columna, 1, filas, columnas);
 	modo = validarModo(modo);

 	if((modo == 'x' || modo == 'X') && tableroMostrar[fila][columna] !=-2){
 		tableroMostrar[fila][columna] == -2;
 		mostrarTablero(filas, columnas, fila, columna, modo, tableroMostrar, tablero, -1);
 		
 		primeraJugada(filas, columnas, numeroMinas, tablero, tableroMostrar, tableroPosiciones);
 	}
 	else if((modo == 'x' || modo == 'X') && tableroMostrar[fila][columna] ==-2){
 		mostrarTablero(filas, columnas, fila, columna, modo, tableroMostrar, tablero, -1);
 		
 		primeraJugada(filas, columnas, numeroMinas, tablero, tableroMostrar, tableroPosiciones);
 	}
 	else{
 		generarTablero(numeroMinas, columnas, filas, tablero, fila, columna);
 		generarInformacion(fila, columna, filas, columnas, tableroMostrar, tablero, -5, tableroPosiciones);
 		tableroPosiciones[fila][columna] = 1;
 		system(LIMPIA);
 		mostrarTablero(filas, columnas, fila, columna, modo, tableroMostrar, tablero, 1);
 		if(validarVictoria(filas, columnas, numeroMinas, tableroMostrar, tablero, tableroPosiciones)==1){
 			printf("%s\n", "¡FELICIDADES! HAS GANADO :D");
 			printf("%s", "Presione enter para salir." );
 			getchar();
 			exit(1);
 		}
 		escribirSolucion(filas, columnas, tablero);
 		jugada(filas, columnas, numeroMinas, tablero, tableroMostrar, tableroPosiciones);
 	}
}

//Función llamada desde el main. Permite iniciar el juego, recibiendo los datos de entrada por parte del usuario.
void iniciarJuego(){
	printf("\n");
	printf("##############BUSCAMINAS V1.0##############\n");
	printf("\n");

	int numeroMinas, columnas, filas, maximoMinas;
	
	printf("Ingrese la cantidad de filas del tablero: ");
	scanf("%i", &filas);
	getchar();
	filas = validarCantidades(filas, 0);

	printf("Ingrese la cantidad de columnas del tablero: ");
	scanf("%i", &columnas);
	getchar();
	columnas = validarCantidades(columnas, 1);

	maximoMinas = (filas*columnas)-2;

	printf("El máximo de minas que puede colocar es: %i\n", maximoMinas);
	printf("Ingrese la cantidad de minas: ");
	scanf("%i", &numeroMinas);
	getchar();

	while(numeroMinas>maximoMinas || numeroMinas<=0){
		printf("Ha ingresado una cantidad inválida de bombas\n");
		printf("Por favor, vuelva a ingresar una cantidad de bombas (menor a %d): ", maximoMinas+1);
		scanf("%i", &numeroMinas);
		getchar();
	}

	int tableroBombas[filas][columnas];
	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			tableroBombas[i][j] = 0;
		}
	}
	int tableroMostrar[filas][columnas];
	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			tableroMostrar[i][j] = -10;
		}
	}
	int tableroPosicionesAbiertas[filas][columnas];
	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			tableroPosicionesAbiertas[i][j] = 0;
		}
	}
	mostrarTablero(filas, columnas, 0, 0, 'a', tableroMostrar, tableroBombas, 0);

	primeraJugada(filas, columnas, numeroMinas, tableroBombas, tableroMostrar, tableroPosicionesAbiertas);

}