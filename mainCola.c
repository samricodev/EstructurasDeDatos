#include <stdio.h>
#include <stdlib.h>
//Codigo explicativo de la TDA Cola

typedef struct nodo{ 
	int valor;
	struct nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;

//Prototipos
void Poner(pNodo *primero, pNodo *ultimom, int v);
int Leer(pNodo *primero, pNodo *ultimo);


int main(int argc, char *argv[]) {
	
	pNodo primero = NULL, ultimo = NULL;
	
	Poner(&primero, &ultimo, 20);
	Poner(&primero,&ultimo, 10);
	printf("Poner(20)\n");
	printf("Poner(10)\n");
	printf("Leer: %d\n", Leer(&primero,&ultimo));
	Poner(&primero,&ultimo,40);
	Poner(&primero,&ultimo,30);
	printf("Poner(40)\n");
	printf("Poner(30)\n");
	
	return 0;
}

void Poner(pNodo *primero, pNodo *ultimo, int valor){
	pNodo nuevo;
	
	//Crear nodo nuevo
	nuevo = (pNodo)malloc(sizeof(tipoNodo));
	nuevo->valor = valor;
	//apuntador siguiente a null
	nuevo->siguiente = NULL;
	//Si la cola esta vacia aniadimos el nuevo al ultimo
	if(*ultimo) (*ultimo)->siguiente = nuevo;
	//ahora el nuevo es el ultimo
	*ultimo = nuevo;
	//Si primero es Null, la cola esta vacia y primero y null apuntara a nuevo
	if(!*primero) *primero = nuevo;
}

int Leer(pNodo *primero, pNodo *ultimo){
	pNodo nodo;
	int v;
	
	//Nodo apunta al primer elemento de la cola
	nodo = *primero;
	//Si nodo que es primero es null, la cola esta vacia y no hay nada por borrar
	if(!nodo) return 0;
	//Asignamos a primero la direccion del segundo nodo
	*primero = nodo->siguiente;
	//Guardamos el valor de retorno
	v = nodo->valor;
	//Borrar
	free(nodo);
	//Si la cola quedo vacia, ultimo debe ser null tambien
	if(!*primero) *ultimo = NULL;
	
	return v;
}
