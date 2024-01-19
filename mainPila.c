#include <stdio.h>
#include <stdlib.h>
//Es una forma de implementar pila
//definicion de la estructura del nodo PILA
typedef struct nodo {
	int valor;
	struct nodo * siguiente;
} tipoNodo;

//definicion de los punteros de pila y nodo de tipo de pila
typedef tipoNodo *pNodo;
typedef tipoNodo *Pila;

//prototipos de funciones Push y Pop
void Push(Pila *Liga, int v);
int Pop(Pila *Liga);

int main(int argc, char *argv[]) {
	
	Pila Liga = NULL;
	
	Push(&Liga, 10);
	Push(&Liga, 30);
	Push(&Liga, 70);
	Push(&Liga, 50);
	
	printf("%d", Pop(&Liga));
	
	return 0;
}

void Push(Pila *Liga, int v){
	pNodo nuevoNodo;
	
	nuevoNodo = (pNodo)malloc(sizeof(tipoNodo));
	nuevoNodo->valor = v;
	nuevoNodo->siguiente = *Liga;
	
	*Liga = nuevoNodo;
}

int Pop(Pila *Liga){
	pNodo nodo;
	int v;
	
	nodo = *Liga;
	if(!nodo) return 0;
	*Liga = nodo->siguiente;
	
	v = nodo->valor;
	free(nodo);
	return v;
}

