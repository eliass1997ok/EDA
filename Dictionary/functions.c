#include "functions.h"

void initializeList(List* list){
	list->first = NULL;
	list->last = NULL;
	list->length = 0;
}

void freeList(Words* words){
	Words* aux;
	while(words != NULL){
		aux = words;
		words = words->nextWord;
		free(aux->spanishWord);
		free(aux->anotherLanguageWord);
		free(aux->spanishMeaning);
		free(aux);
	}
}

void clearScreen(){
	#ifdef _WIN32
		system("cls");
	#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
		system("clear");
	#else
		#error "Sistema Operativo no soportado."
	#endif
}

Node** createNodes(List* list){
	Words* aux;
	aux = list->first;

	Node** nodesOfTree;
	nodesOfTree = (Node**)calloc(list->length, sizeof(Node*));

	for(int i=0; i<list->length; i++){
		nodesOfTree[i] = (Node*)calloc(1, sizeof(Node));
		nodesOfTree[i]->spanishWord = (char*)calloc(100, sizeof(char));
		nodesOfTree[i]->anotherLanguageWord = (char*)calloc(100, sizeof(char));
		nodesOfTree[i]->spanishMeaning = (char*)calloc(1024, sizeof(char));
		nodesOfTree[i]->spanishFather = (Node*)calloc(1, sizeof(Node));
		nodesOfTree[i]->anotherLanguageFather = (Node*)calloc(1, sizeof(Node));
		nodesOfTree[i]->spanishLeftSon = (Node*)calloc(1, sizeof(Node));
		nodesOfTree[i]->spanishRightSon = (Node*)calloc(1, sizeof(Node));
		nodesOfTree[i]->anotherLanguageLeftSon = (Node*)calloc(1, sizeof(Node));
		nodesOfTree[i]->anotherLanguageRightSon = (Node*)calloc(1, sizeof(Node));
	}

	int position = 0;

	while(aux != NULL){
		strcpy(nodesOfTree[position]->spanishWord, aux->spanishWord);
		strcpy(nodesOfTree[position]->anotherLanguageWord, aux->anotherLanguageWord);
		strcpy(nodesOfTree[position]->spanishMeaning, aux->spanishMeaning);
		nodesOfTree[position]->spanishFather = NULL;
		nodesOfTree[position]->anotherLanguageFather = NULL;
		nodesOfTree[position]->spanishLeftSon = NULL;
		nodesOfTree[position]->spanishRightSon = NULL;
		nodesOfTree[position]->anotherLanguageLeftSon = NULL;
		nodesOfTree[position]->anotherLanguageRightSon = NULL;

		position++;
		aux = aux->nextWord;
	}

	freeList(list->first);
	return nodesOfTree;
}

int alphabetPosition(char letter){
	char* alphabet = "AaáBbCcçDdEeéFfGgǵHhIiíJjKkḱLlĺMmḿNnńÑñOoóPpṕQqRrŕSsśTtUuúVvǘWwXxYyýZzź";
	for(int i=0; i<strlen(alphabet); i++){
		if(letter == alphabet[i]){
			return i;
		}
	}
	return -1;
}

int wordsCompare(char* firstWord, char* secondWord){
	int i = 0;
	
	if (strlen(firstWord) > strlen(secondWord)){
		while(i<strlen(secondWord)){
			if(alphabetPosition(firstWord[i]) > alphabetPosition(secondWord[i])){
				return -1;
			}
			else if(alphabetPosition(firstWord[i]) < alphabetPosition(secondWord[i])){
				return 1;
			}
			else{
				i++;
			}
		}
		return -1;
	}
	else if(strlen(firstWord) < strlen(secondWord)){
		while(i<strlen(firstWord)){
			if(alphabetPosition(firstWord[i]) > alphabetPosition(secondWord[i])){
				return -1;
			}
			else if(alphabetPosition(firstWord[i]) < alphabetPosition(secondWord[i])){
				return 1;
			}
			else{
				i++;
			}
		}
		return 1;
	}
	else{
		while(i<strlen(firstWord)){
			if(alphabetPosition(firstWord[i]) > alphabetPosition(secondWord[i])){
				return -1;
			}
			else if(alphabetPosition(firstWord[i]) < alphabetPosition(secondWord[i])){
				return 1;
			}
			else{
				i++;
			}
		}
		return 0;
	}
}

void appendWord(List* list, char* spanishWord, char* anotherLanguageWord, char* spanishMeaning){
	Words* node;
	node = (Words*)calloc(1, sizeof(Words));

	node->spanishWord = (char*)calloc(100, sizeof(char));
	node->anotherLanguageWord = (char*)calloc(100, sizeof(char));
	node->spanishMeaning = (char*)calloc(1024, sizeof(char));

	strcpy(node->spanishWord, spanishWord);
	strcpy(node->anotherLanguageWord, anotherLanguageWord);
	strcpy(node->spanishMeaning, spanishMeaning);

	node->nextWord = NULL;

	if(list->length == 0){
		list->first = node;
		list->last = node;
	}
	else{
		list->last->nextWord = node;
		list->last = node;
	}
	list->length++;
}

List* readFile(){
	FILE* f;
	f = fopen("Diccionario.in", "r");
	if( ! f){
		perror("Diccionario.in");
		exit(1);
	}
	List* words;
	words = (List*)calloc(1, sizeof(List));
	initializeList(words);
	//5
	while( ! feof(f) ){
		char line[1024];
		char* token;
		char* spanishWord;
		char* anotherLanguageWord;
		char* spanishMeaning;
		spanishWord = (char*)calloc(100, sizeof(char));
		anotherLanguageWord = (char*)calloc(100, sizeof(char));
		spanishMeaning = (char*)calloc(1024, sizeof(char));

		fgets(line, 1024, f);

		token = strtok(line, " ");
		token[0] = tolower(token[0]);
		strcpy(spanishWord, token);
		token = strtok(NULL, " ");
		token[0] = tolower(token[0]);
		strcpy(anotherLanguageWord, token);
		token = strtok(NULL, "");
		token[0] = tolower(token[0]);
		strcpy(spanishMeaning, token);	
		appendWord(words, spanishWord, anotherLanguageWord, spanishMeaning);
	}

	return words;
}

int heightSpanishNode(Node* node){
	int leftHeight;
	int rigthHeigth;

	if(node->spanishRightSon == NULL && node->spanishLeftSon == NULL){
		return 0;
	}
	if(node->spanishRightSon == NULL){
		rigthHeigth = 0;
	}
	else{
		rigthHeigth = heightSpanishNode(node->spanishRightSon);
	}
	if(node->spanishLeftSon == NULL){
		leftHeight = 0;
	}
	else{
		leftHeight = heightSpanishNode(node->spanishLeftSon);
	}
	if(leftHeight > rigthHeigth){
		return leftHeight+1;
	}
	else{
		return rigthHeigth+1;
	}
}

int heightAnotherLanguageNode(Node* node){
	int leftHeight;
	int rigthHeight;
	if(node->anotherLanguageRightSon == NULL && node->anotherLanguageLeftSon == NULL){
		return 0;
	}
	if(node->anotherLanguageRightSon == NULL){
		rigthHeight = 0;
	}
	else{
		rigthHeight = heightAnotherLanguageNode(node->anotherLanguageRightSon);
	}
	if(node->anotherLanguageLeftSon == NULL){
		leftHeight = 0;
	}
	else{
		leftHeight = heightAnotherLanguageNode(node->anotherLanguageLeftSon);
	}
	if(leftHeight > rigthHeight){
		return leftHeight+1;
	}
	else{
		return rigthHeight+1;
	}
}

int differenceBetweenHeightInSpanish(Node* node){
	int leftHeight;
	int rigthHeight;
	if(node->spanishRightSon != NULL || node->spanishLeftSon != NULL){
		if(node->spanishRightSon != NULL && node->spanishLeftSon != NULL){
			leftHeight = heightSpanishNode(node->spanishLeftSon);
			rigthHeight = heightSpanishNode(node->spanishRightSon);
			return leftHeight - rigthHeight;
		}
		if(node->spanishRightSon == NULL){
			return 1+heightSpanishNode(node->spanishLeftSon);
		}
		if(node->spanishLeftSon == NULL){
			return 0-(1+heightSpanishNode(node->spanishRightSon));
		}
		return 0;
	}
	else{
		return 0;
	}
}

int differenceBetweenHeightInAnotherLanguage(Node* node){
	int leftHeight;
	int rigthHeight;
	if(node->anotherLanguageRightSon != NULL || node->anotherLanguageLeftSon != NULL){
		if(node->anotherLanguageRightSon != NULL && node->anotherLanguageLeftSon != NULL){
			leftHeight = heightAnotherLanguageNode(node->anotherLanguageLeftSon);
			rigthHeight = heightAnotherLanguageNode(node->anotherLanguageRightSon);
			return leftHeight - rigthHeight;
		}
		if(node->anotherLanguageRightSon == NULL){
			return 1+heightAnotherLanguageNode(node->anotherLanguageLeftSon);
		}
		if(node->anotherLanguageLeftSon == NULL){
			return 0-(1+heightAnotherLanguageNode(node->anotherLanguageRightSon));
		}
		return 0;
	}
	else{
		return 0;
	}
}

void rotateLeftSpanishTree(Tree* tree, Node* node){
	Node* root;
	root = node->spanishRightSon;
	if(node->spanishFather == NULL){
		tree->spanishRoot = root;
	}
	else{
		if(node == node->spanishFather->spanishLeftSon){
			node->spanishFather->spanishLeftSon = root;
		}
		else{
			node->spanishFather->spanishRightSon = root;
		}
	}
	node->spanishRightSon = root->spanishLeftSon;
	root->spanishLeftSon = node;
	root->spanishFather = node->spanishFather;
	root->spanishLeftSon->spanishFather = root;
	if(root->spanishRightSon != NULL){
		root->spanishRightSon->spanishFather = root;
	}
}

void rotateLeftAnotherLanguageTree(Tree* tree, Node* node){
	Node* root;
	root = node->anotherLanguageRightSon;
	if(node->anotherLanguageFather == NULL){
		tree->anotherLanguageRoot = root;
	}
	else{
		if(node == node->anotherLanguageFather->anotherLanguageLeftSon){
			node->anotherLanguageFather->anotherLanguageLeftSon = root;
		}
		else{
			node->anotherLanguageFather->anotherLanguageRightSon = root;
		}
	}
	node->anotherLanguageRightSon = root->anotherLanguageLeftSon;
	root->anotherLanguageLeftSon = node;
	root->anotherLanguageFather = node->anotherLanguageFather;
	root->anotherLanguageLeftSon->anotherLanguageFather = root;
	if(root->anotherLanguageRightSon != NULL){
		root->anotherLanguageRightSon->anotherLanguageFather = root;
	}
}

void rotateRightSpanishTree(Tree* tree, Node* node){
	Node* root;
	root = node->spanishLeftSon;
	if(node->spanishFather == NULL){
		tree->spanishRoot = root;
	}
	else{
		if(node == node->spanishFather->spanishLeftSon){
			node->spanishFather->spanishLeftSon = root;
		}
		else{
			node->spanishFather->spanishRightSon = root;
		}
	}
	node->spanishLeftSon = root->spanishRightSon;
	root->spanishRightSon = node;
	root->spanishFather = node->spanishFather;
	root->spanishRightSon->spanishFather = root;
	if(root->spanishLeftSon != NULL){
		root->spanishLeftSon->spanishFather = root;
	}	
}

void rotateRightAnotherLanguageTree(Tree* tree, Node* node){
	Node* root;
	root = node->anotherLanguageLeftSon;
	if(node->anotherLanguageFather == NULL){
		tree->anotherLanguageRoot = root;
	}
	else{
		if(node == node->anotherLanguageFather->anotherLanguageLeftSon){
			node->anotherLanguageFather->anotherLanguageLeftSon = root;
		}
		else{
			node->anotherLanguageFather->anotherLanguageRightSon = root;
		}
	}
	node->anotherLanguageLeftSon = root->anotherLanguageRightSon;
	root->anotherLanguageRightSon = node;
	root->anotherLanguageFather = node->anotherLanguageFather;
	root->anotherLanguageRightSon->anotherLanguageFather = root;
	if(root->anotherLanguageLeftSon != NULL){
		root->anotherLanguageLeftSon->anotherLanguageFather = root;
	}	
}

void balanceSpanishTree(Tree* tree, Node* node){
	int difference1;
	int difference2;

	difference1 = differenceBetweenHeightInSpanish(node);
	if(difference1 > 1){
		difference2 = differenceBetweenHeightInSpanish(node->spanishLeftSon);
		if(difference2 < 0){
			rotateLeftSpanishTree(tree, node->spanishLeftSon);
		}
		rotateRightSpanishTree(tree, node);
	}
	if(difference1 < -1){
		difference2 = differenceBetweenHeightInSpanish(node->spanishRightSon);
		if(difference2 > 0){
			rotateRightSpanishTree(tree, node->spanishRightSon);
		}
		rotateLeftSpanishTree(tree, node);
	}
}

void balanceAnotherLanguageTree(Tree* tree, Node* node){
	int difference1;
	int difference2;

	difference1 = differenceBetweenHeightInAnotherLanguage(node);
	if(difference1 > 1){
		difference2 = differenceBetweenHeightInAnotherLanguage(node->anotherLanguageLeftSon);
		if(difference2 < 0){
			rotateLeftAnotherLanguageTree(tree, node->anotherLanguageLeftSon);
		}
		rotateRightAnotherLanguageTree(tree, node);
	}
	if(difference1 < -1){
		difference2 = differenceBetweenHeightInAnotherLanguage(node->anotherLanguageRightSon);
		if(difference2 > 0){
			rotateRightAnotherLanguageTree(tree, node->anotherLanguageRightSon);
		}
		rotateLeftAnotherLanguageTree(tree, node);
	}
}

void insertAnotherLanguageTree(Tree* tree, Node* nodeToInsert){
	Node* a;
	Node* p;

	if(tree->anotherLanguageRoot == NULL){
		tree->anotherLanguageRoot = nodeToInsert;
		return;
	}
	else{	
		a = tree->anotherLanguageRoot;
	}


	while(a != NULL){
		p = a;

		if(wordsCompare(a->anotherLanguageWord, nodeToInsert->anotherLanguageWord) == -1){
			a = a->anotherLanguageLeftSon;
		}
		else{
			a = a->anotherLanguageRightSon;
		}
	}

	if(wordsCompare(p->anotherLanguageWord, nodeToInsert->anotherLanguageWord) == -1){
		p->anotherLanguageLeftSon = nodeToInsert;
	}
	else{
		p->anotherLanguageRightSon = nodeToInsert;
	}
	nodeToInsert->anotherLanguageFather = p;

	while(p!=NULL){
		balanceAnotherLanguageTree(tree, p);
		p = p->anotherLanguageFather;
	}
}

void insertSpanishInTree(Tree* tree, Node* nodeToInsert){
	Node* a;
	Node* p;
	if(tree->spanishRoot == NULL){
		tree->spanishRoot = nodeToInsert;
		return;
	}
	else{
		a = tree->spanishRoot;
	}

	while(a != NULL){
		p = a;
		if(wordsCompare(a->spanishWord, nodeToInsert->spanishWord) == -1){
			a = a->spanishLeftSon;
		}
		else{
			a = a->spanishRightSon;
		}
	}
	if(wordsCompare(p->spanishWord, nodeToInsert->spanishWord) == -1){
		p->spanishLeftSon = nodeToInsert;
	}
	else{
		p->spanishRightSon = nodeToInsert;
	}
	nodeToInsert->spanishFather = p;

	while(p!=NULL){
		balanceSpanishTree(tree, p);
		p = p->spanishFather;
	}
}

void inOrderSpanish(Node* node, FILE* f){
	if(node != NULL){
		inOrderSpanish(node->spanishLeftSon, f);
		fprintf(f, "%s ", node->spanishWord);
		fprintf(f, "%s ", node->anotherLanguageWord);
		if(node->spanishLeftSon == NULL){
			fprintf(f, "(NULL ");
		}
		else{
			fprintf(f, "(%s ", node->spanishLeftSon->spanishWord);
		}
		if(node->spanishRightSon == NULL){
			fprintf(f, "NULL)");	
		}
		else{
			fprintf(f, "%s)", node->spanishRightSon->spanishWord);
		}
		fprintf(f, " - ");
		if(node->anotherLanguageLeftSon == NULL){
			fprintf(f, "(NULL ");
		}
		else{
			fprintf(f, "(%s ", node->anotherLanguageLeftSon->anotherLanguageWord);
		}
		if(node->anotherLanguageRightSon == NULL){
			fprintf(f, "NULL)\n");	
		}
		else{
			fprintf(f, "%s)\n", node->anotherLanguageRightSon->anotherLanguageWord);
		}
		inOrderSpanish(node->spanishRightSon, f);
	}
}

void inOrderAnotherLanguage(Node* node, FILE* f){
	if(node != NULL){
		inOrderAnotherLanguage(node->anotherLanguageLeftSon, f);
		fprintf(f, "%s ", node->spanishWord);
		fprintf(f, "%s ", node->anotherLanguageWord);
		if(node->spanishLeftSon == NULL){
			fprintf(f, "(NULL ");
		}
		else{
			fprintf(f, "(%s ", node->spanishLeftSon->spanishWord);
		}
		if(node->spanishRightSon == NULL){
			fprintf(f, "NULL)");	
		}
		else{
			fprintf(f, "%s)", node->spanishRightSon->spanishWord);
		}
		fprintf(f, " - ");
		if(node->anotherLanguageLeftSon == NULL){
			fprintf(f, "(NULL ");
		}
		else{
			fprintf(f, "(%s ", node->anotherLanguageLeftSon->anotherLanguageWord);
		}
		if(node->anotherLanguageRightSon == NULL){
			fprintf(f, "NULL)\n");	
		}
		else{
			fprintf(f, "%s)\n", node->anotherLanguageRightSon->anotherLanguageWord);
		}
		inOrderAnotherLanguage(node->anotherLanguageRightSon, f);
	}
}

char* searchSpanishMeaning(Node* node, char* wordToSearch){
	if(node != NULL){
		if(wordsCompare(node->spanishWord, wordToSearch) == 0){
			return node->spanishMeaning;
		}
		else if(wordsCompare(node->spanishWord, wordToSearch) < 0){
			return searchSpanishMeaning(node->spanishLeftSon, wordToSearch);
		}
		else{
			return searchSpanishMeaning(node->spanishRightSon, wordToSearch);
		}
	}
	else{
		return "NOMATCHFORSEARCH";
	}
}

char* searchAnotherLanguageMeaning(Node* node, char* wordToSearch){
	if(node != NULL){
		if(wordsCompare(node->anotherLanguageWord, wordToSearch) == 0){
			return node->spanishMeaning;
		}
		else if(wordsCompare(node->anotherLanguageWord, wordToSearch) < 0){
			return searchAnotherLanguageMeaning(node->anotherLanguageLeftSon, wordToSearch);
		}
		else{
			return searchAnotherLanguageMeaning(node->anotherLanguageRightSon, wordToSearch);
		}
	}
	else{
		return "NOMATCHFORSEARCH";
	}
}

char* searchSpanishToAnotherLanguageTranslation(Node* node, char* spanishWord){
	if(node != NULL){
		if(wordsCompare(node->spanishWord, spanishWord) == 0){
			return node->anotherLanguageWord;
		}
		else if(wordsCompare(node->spanishWord, spanishWord) < 0){
			return searchSpanishToAnotherLanguageTranslation(node->spanishLeftSon, spanishWord);
		}
		else{
			return searchSpanishToAnotherLanguageTranslation(node->spanishRightSon, spanishWord);
		}
	}
	else{
		return "NOMATCHFORSEARCH";
	}
}

char* searchAnotherLanguageToSpanishTranslation(Node* node, char* anotherLanguageWord){
	if(node != NULL){
		if(wordsCompare(node->anotherLanguageWord, anotherLanguageWord) == 0){
			return node->spanishWord;
		}
		else if(wordsCompare(node->anotherLanguageWord, anotherLanguageWord) < 0){
			return searchAnotherLanguageToSpanishTranslation(node->anotherLanguageLeftSon, anotherLanguageWord);
		}
		else{
			return searchAnotherLanguageToSpanishTranslation(node->anotherLanguageRightSon, anotherLanguageWord);
		}
	}
	else{
		return "NOMATCHFORSEARCH";
	}
}

void writeInOrderSpanishTree(Node* node){
	FILE* f;
	f = fopen("Solution.out", "w");
	fprintf(f, "Ordenado alfabéticamente a partir del español\n\n");
	inOrderSpanish(node, f);
	fclose(f);
}

void writeInOrderAnotherLanguageTree(Node* node){
	FILE* f;
	f = fopen("Solution.out", "w");
	fprintf(f, ">>>Ordenado alfabéticamente a partir del inglés\n\n");
	inOrderAnotherLanguage(node, f);
	fclose(f);
}

void menu(Tree* tree){
	int choice;
	printf("######### DICCIONARIO / TRADUCTOR V.1.0 #########\n\n");
	printf("[1] Buscar traducción de español a otro idioma.\n");
	printf("[2] Buscar traducción de otro idioma a español.\n");
	printf("[3] Buscar significado de una palabra en español.\n");
	printf("[4] Buscar significado de una palabra en español a partir de una palabra en otro idioma.\n");
	printf("[5] Generar archivo con las palabras ordenadas en español contenidas en el árbol.\n");
	printf("[6] Generar archivo con las palabras ordenadas en otro idioma contenidas en el árbol.\n");
	printf("\n");
	printf("[9] Salir del programa.\n");
	printf("\n");
	printf("Ingrese una de las opciones: \n");
	printf("[>] ");
	scanf("%d", &choice);
	while(choice<1 || choice >9 || (choice > 6 && choice < 9)){
		clearScreen();
		printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
		printf("[1] Buscar traducción de español a otro idioma.\n");
		printf("[2] Buscar traducción de otro idioma a español.\n");
		printf("[3] Buscar significado de una palabra en español.\n");
		printf("[4] Buscar significado de una palabra en español a partir de una palabra en otro idioma.\n");
		printf("[5] Generar archivo con las palabras ordenadas en español contenidas en el árbol.\n");
		printf("[6] Generar archivo con las palabras ordenadas en otro idioma contenidas en el árbol.\n");
		printf("\n");
		printf("[9] Salir del programa.\n");
		printf("\n");
		printf("Ingrese una de las opciones: \n");
		printf("[>] ");
		getchar();
		scanf("%d", &choice);
	}

	switch(choice){
		case 1: ;
			clearScreen();
			char spanishWordToSearch[200];
			char translatedWord[200];
			printf("Ingrese la palabra en español a traducir: ");
			scanf("%s", spanishWordToSearch);
			spanishWordToSearch[0] = tolower(spanishWordToSearch[0]);
			strcpy(translatedWord, searchSpanishToAnotherLanguageTranslation(tree->spanishRoot, spanishWordToSearch));
			if(strcmp(translatedWord, "NOMATCHFORSEARCH") == 0){
				int newQuery;
				clearScreen();
				printf("Palabra consultada: %s\n", spanishWordToSearch);
				printf("La consulta no arrojó resultados.\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				getchar();
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					getchar();
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			else{
				int newQuery;
				clearScreen();
				printf("La traducción de %s es: %s\n", spanishWordToSearch, translatedWord);
				printf("\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			break;
		case 2: 
			clearScreen();
			char anotherLanguageWordToSearch[200];
			char translatedWordToSpanish[200];
			printf("Ingrese la palabra a buscar traducción en español: ");
			scanf("%s", anotherLanguageWordToSearch);
			anotherLanguageWordToSearch[0] = tolower(anotherLanguageWordToSearch[0]);
			strcpy(translatedWordToSpanish, searchAnotherLanguageToSpanishTranslation(tree->anotherLanguageRoot, anotherLanguageWordToSearch));
			if(strcmp(translatedWordToSpanish, "NOMATCHFORSEARCH") == 0){
				int newQuery;
				clearScreen();
				printf("Palabra consultada: %s\n", anotherLanguageWordToSearch);
				printf("La consulta no arrojó resultados.\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				getchar();
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					getchar();
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			else{
				int newQuery;
				clearScreen();
				printf("La traducción de %s es: %s\n", anotherLanguageWordToSearch, translatedWordToSpanish);
				printf("\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			break;
		case 3:
			clearScreen();
			char spanishWordToSearchMeaning[200];
			char spanishMeaning[2000];
			printf("Ingrese la palabra en español de la cual desea saber su significado: ");
			scanf("%s", spanishWordToSearchMeaning);
			spanishWordToSearchMeaning[0] = tolower(spanishWordToSearchMeaning[0]);
			strcpy(spanishMeaning, searchSpanishMeaning(tree->spanishRoot, spanishWordToSearchMeaning));
			if(strcmp(spanishMeaning, "NOMATCHFORSEARCH") == 0){
				int newQuery;
				clearScreen();
				printf("Palabra consultada: %s\n", spanishWordToSearchMeaning);
				printf("La consulta no arrojó resultados.\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				getchar();
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					getchar();
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			else{
				int newQuery;
				clearScreen();
				printf("El significado en español de %s es: %s\n", spanishWordToSearchMeaning, spanishMeaning);
				printf("\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			break;
		case 4:
			clearScreen();
			char anotherLanguageWordToSearchMeaning[200];
			char spanishMeaningByAnotherLanguageWord[2000];
			printf("Ingrese la palabra en otro idioma de la cual desea saber su significado en español: ");
			scanf("%s", anotherLanguageWordToSearchMeaning);
			anotherLanguageWordToSearchMeaning[0] = tolower(anotherLanguageWordToSearchMeaning[0]);
			strcpy(spanishMeaningByAnotherLanguageWord, searchAnotherLanguageMeaning(tree->anotherLanguageRoot, anotherLanguageWordToSearchMeaning));
			if(strcmp(spanishMeaningByAnotherLanguageWord, "NOMATCHFORSEARCH") == 0){
				int newQuery;
				clearScreen();
				printf("Palabra consultada: %s\n", anotherLanguageWordToSearchMeaning);
				printf("La consulta no arrojó resultados.\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				getchar();
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					getchar();
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			else{
				int newQuery;
				clearScreen();
				printf("El significado en español de %s es: %s\n", anotherLanguageWordToSearchMeaning, spanishMeaningByAnotherLanguageWord);
				printf("\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				scanf("%d", &newQuery);
				while(newQuery<1 || newQuery>2){
					clearScreen();
					printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
					printf("\n");
					printf("¿Desea realizar una nueva operación?\n");
					printf("[1] Sí\n");
					printf("[2] No\n");
					printf("\n");
					printf("Ingrese una de las opciones: \n");
					printf("[>] ");
					scanf("%d", &newQuery);
				}
				if(newQuery == 1){
					clearScreen();
					menu(tree);
				}
				else{
					printf("Cerrando el programa...\n");
					exit(1);
				}
			}
			break;
		case 5:
			clearScreen();
			printf("Escribiendo archivo...\n");
			writeInOrderSpanishTree(tree->spanishRoot);
			printf("Archivo escrito satisfactoriamente!\n");
			int newQuery;
			printf("\n");
			printf("¿Desea realizar una nueva operación?\n");
			printf("[1] Sí\n");
			printf("[2] No\n");
			printf("\n");
			printf("Ingrese una de las opciones: \n");
			printf("[>] ");
			scanf("%d", &newQuery);
			while(newQuery<1 || newQuery>2){
				clearScreen();
				printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
				printf("\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				scanf("%d", &newQuery);
			}
			if(newQuery == 1){
				clearScreen();
				menu(tree);
			}
			else{
				printf("Cerrando el programa...\n");
				exit(1);
			}
			break;
		case 6:
			clearScreen();
			printf("Escribiendo archivo...\n");
			writeInOrderAnotherLanguageTree(tree->anotherLanguageRoot);
			printf("Archivo escrito satisfactoriamente!\n");
			int newQuery2;
			printf("\n");
			printf("¿Desea realizar una nueva operación?\n");
			printf("[1] Sí\n");
			printf("[2] No\n");
			printf("\n");
			printf("Ingrese una de las opciones: \n");
			printf("[>] ");
			scanf("%d", &newQuery2);
			while(newQuery2<1 || newQuery2>2){
				clearScreen();
				printf("Ha ingresado una opción no válida. Vuelva a ingresar una opción.\n");
				printf("\n");
				printf("¿Desea realizar una nueva operación?\n");
				printf("[1] Sí\n");
				printf("[2] No\n");
				printf("\n");
				printf("Ingrese una de las opciones: \n");
				printf("[>] ");
				scanf("%d", &newQuery2);
			}
			if(newQuery2 == 1){
				clearScreen();
				menu(tree);
			}
			else{
				printf("Cerrando el programa...\n");
				exit(1);
			}
			break;
		case 9:
			printf("Cerrando el programa...\n");
			exit(1);
			break;
	}
}

void run(){
	List* words;
	Node** nodesOfTree;
	Tree* tree;

	tree = (Tree*)calloc(1, sizeof(Tree));
	tree->spanishRoot = NULL;
	tree->anotherLanguageRoot = NULL;

	words = readFile();

	int amountOfWords = words->length;

	nodesOfTree = createNodes(words);

	for(int i=0; i<amountOfWords; i++){
		insertSpanishInTree(tree, nodesOfTree[i]);
		insertAnotherLanguageTree(tree, nodesOfTree[i]);
	}

	clearScreen();
	menu(tree);

}