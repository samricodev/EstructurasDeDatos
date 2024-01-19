#include <stdio.h>
#include <stdlib.h>
//Es una forma de implementar pila con chars
//definicion de la estructura del nodo PILA
typedef struct nodo {
	char valor;
	struct nodo * siguiente;
} tipoNodo;

//definicion de los punteros de pila y nodo de tipo de pila
typedef tipoNodo *pNodo;
typedef tipoNodo *Pila;

//prototipos de funciones Push y Pop
void Push(Pila *Liga, char v);
char Pop(Pila *Liga);

int main(int argc, char *argv[]) {
	
	Pila Liga = NULL;
	int i, j, contador, del;
	char v;
	
	printf("Cuantos nodos deseas crear: ");
	scanf("%d", &contador);
	scanf("%c",&v);
	for(i = 0; i < contador; i++){
		scanf("%c",&v);
		printf("\nEscribe tu valor de caracter para el nodo %d: ",i+1);
		scanf("%c",&v);
		Push(&Liga,v);
	}
	
	printf("Tienes %d nodos, cuantos deseas eliminar?", contador);
	scanf("%d",&del);
	contador -= del;
	
	for(j = 0; j < del; j++){
		printf("\nValor eliminado: %c", Pop(&Liga));
	}
	
	printf("\nTu pila tiene %d nodos", contador);
	return 0;
}

void Push(Pila *Liga, char v){
	pNodo nuevoNodo;
	
	nuevoNodo = (pNodo)malloc(sizeof(tipoNodo));
	nuevoNodo->valor = v;
	nuevoNodo->siguiente = *Liga;
	
	*Liga = nuevoNodo;
}

char Pop(Pila *Liga){
	pNodo nodo;
	char v;
	
	nodo = *Liga;
	if(!nodo) return 0;
	*Liga = nodo->siguiente;
	
	v = nodo->valor;
	free(nodo);
	return v;
}
