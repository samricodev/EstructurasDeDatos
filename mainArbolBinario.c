#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

//Arbol Binario base
struct Nodo{
	int dato;
	struct Nodo *izq;
	struct Nodo *der;
	struct Nodo *padre;
};

//size-t es un tipo de dato sin signo, que es mayor a 0
struct Nodo *nuevoNodo (int dato, struct Nodo *padre){
	size_t tamaNodo = sizeof(struct Nodo);
	struct Nodo *nodo = (struct Nodo *)malloc(tamaNodo);
	nodo->dato = dato;
	nodo->der = nodo->izq = NULL;
	nodo->padre = padre;

	return nodo;			
}

//Prototipos de funciones
void insertar(struct Nodo *raiz,struct Nodo *padre, int dato);
void preOrden(struct Nodo *raiz);
void inOrden(struct Nodo *raiz);
void posOrden(struct Nodo *raiz);
bool busqueda(struct Nodo *raiz, int dato);
void eliminar(struct Nodo *raiz, int n);
void eliminarNodo(struct Nodo *nodoEliminar);
void reemplazar(struct Nodo *raiz, struct Nodo *nuevo);
void destruirNodo(struct Nodo *nodoDestruir);
struct Nodo *minimo(struct Nodo *raiz);
//void Borrar(Nodo *raiz, int dato);

int main(int argc, char *argv[]) {
	
	struct Nodo *raiz = nuevoNodo(28,NULL);
	int borrar = 1, buscar = 6;
	
	insertar(raiz,NULL,11);
	insertar(raiz,NULL,96);
	insertar(raiz,NULL,21);
	insertar(raiz,NULL,6);
	insertar(raiz,NULL,97);
	insertar(raiz,NULL,1);
	insertar(raiz,NULL,30);
	insertar(raiz,NULL,10);
	insertar(raiz,NULL,2);
	
	if(busqueda(raiz,buscar)){
		printf("\nDato %d encontrado", buscar);
	} else{
		printf("\nDato no encontrado");
	}
	
	printf("\nPre Orden:\n");
	preOrden(raiz);
	printf("\nIn Orden:\n");
	inOrden(raiz);
	printf("\nPos Orden:\n");
	posOrden(raiz);
	
	eliminar(raiz,30);
	
	printf("\nIn Orden:\n");
	inOrden(raiz);
	
	return 0;
}

void insertar(struct Nodo *raiz, struct Nodo *padre, int dato){
	//Si es mayor va a la derecha
	if(dato > raiz->dato){
		if(raiz->der == NULL){
			raiz->der = nuevoNodo(dato,padre);
		}else{
			insertar(raiz->der, padre,dato);	
		}
	}else{
		//sino a la izq
		if(raiz->izq == NULL){
			raiz->izq = nuevoNodo(dato,padre);
		}else{
			insertar(raiz->izq, padre, dato);
		}
	}
}

bool busqueda(struct Nodo *arbol,int n){
	if(arbol == NULL){
		return false;
	}
	else if(arbol->dato == n){ 
		return true;
	}
	else if(n < arbol->dato){
		return busqueda(arbol->izq, n);
	}
	else{
		return busqueda(arbol->der,n);
	}
}


void preOrden(struct Nodo *raiz){
	if(raiz != NULL){
		printf("%d ",raiz->dato);
		preOrden(raiz->izq);
		preOrden(raiz->der);
	}
}

void inOrden(struct Nodo *raiz){
	if(raiz != NULL){
		inOrden(raiz->izq);
		printf("%d ",raiz->dato);
		inOrden(raiz->der);
	}
}

void posOrden(struct Nodo *raiz){
	if(raiz != NULL){
		posOrden(raiz->izq);
		posOrden(raiz->der);
		printf("%d ",raiz->dato);
	}
}

void eliminar(struct Nodo *arbol, int n){
	if(arbol == NULL){
		return;
	} else if(n < arbol->dato){
		eliminar(arbol->izq, n);
	} else if(n > arbol->dato){
		eliminar(arbol->der, n);
	}else{
		eliminarNodo(arbol);
	}
}

struct Nodo *minimo(struct Nodo *arbol){
	if(arbol == NULL){
		return NULL;
	} 
	if(arbol->izq){
		return minimo(arbol->izq);
	} else{
		return arbol;
	}
}

void reemplazar(struct Nodo *arbol, struct Nodo *nuevo){
	if(arbol->padre){
		if(arbol->dato == arbol->padre->izq->dato){
			arbol->padre->izq = nuevo;
		} else if(arbol->dato == arbol->padre->der->dato){
			arbol->padre->der = nuevo;
		}
	}
	
	if(nuevo){
		nuevo->padre = arbol->padre;
	}
}

void destruirNodo(struct Nodo *nodo){
	nodo->izq = NULL;
	nodo->der = NULL;
	
	free(nodo);
}

void eliminarNodo(struct Nodo *nodoEliminar){
	if(nodoEliminar->izq && nodoEliminar->der){
		struct Nodo *menor = minimo(nodoEliminar->der);
		nodoEliminar->dato = menor->dato;
		eliminarNodo(menor);
	} else if(nodoEliminar->izq){
		reemplazar(nodoEliminar, nodoEliminar->izq);
		destruirNodo(nodoEliminar);
	} else if(nodoEliminar->der){
		reemplazar(nodoEliminar, nodoEliminar->der);
		destruirNodo(nodoEliminar);
	} else{
		reemplazar(nodoEliminar,NULL);
		destruirNodo(nodoEliminar);
	}
}
