#include <stdlib.h>
#include <stdio.h>

typedef struct nodo {
   int valor;
   struct nodo *siguiente;
} tipoNodo;


typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

/* Funciones con listas: */
void Insertar(Lista *l, int v);
void Borrar(Lista *l, int v);
int ListaVacia(Lista l);
void BorrarLista(Lista *l);
void MostrarLista(Lista l);

int main(int argc, char *argv[]) {
	Lista lista = NULL;
	int i, j, n, dato, borrar;
	//Insertar
	printf("Ingresa la cantidad de nodos a ingresar: ");
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		printf("Ingresa el valor del nodo: ");
		scanf("%d",&dato);
		Insertar(&lista, dato);
	}
	
	printf("\n");
	MostrarLista(lista);
	
	//Borrar
	printf("\nCuantos nodos deseas borrar: ");
	scanf("%d", &borrar);
	for(j = 0; j < borrar; j++){
		printf("Ingresa el valor del nodo a borrar: ");
		scanf("%d",&dato);
		Borrar(&lista, dato);
	}
	
	printf("\n");
	MostrarLista(lista);

	BorrarLista(&lista);

	return 0;
}

void Insertar(Lista *lista, int v) {
   pNodo nuevo, anterior;

   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->valor = v;

   if(ListaVacia(*lista) || (*lista)->valor > v) {
      nuevo->siguiente = *lista;
      *lista = nuevo;
   } else {
      anterior = *lista;
      while(anterior->siguiente && anterior->siguiente->valor <= v){
      	anterior = anterior->siguiente;
	  }
    	nuevo->siguiente = anterior->siguiente;
    	anterior->siguiente = nuevo;
	  
   }
}

void Borrar(Lista *lista, int v) {
   pNodo anterior, nodo;

   nodo = *lista;
   anterior = NULL;
   while(nodo && nodo->valor < v) {
      anterior = nodo;
      nodo = nodo->siguiente;
   }
   if(!nodo || nodo->valor != v) return;
   else { /* Borrar el nodo */
      if(!anterior) *lista = nodo->siguiente;
      else{
      	anterior->siguiente = nodo->siguiente;	
	  }
    	free(nodo);
     
   }
}

int ListaVacia(Lista lista) {
   return (lista == NULL);
}

void BorrarLista(Lista *lista) {
   pNodo nodo;

   while(*lista) {
      nodo = *lista;
      *lista = nodo->siguiente;
      free(nodo);
   }
}

void MostrarLista(Lista lista) {
   pNodo nodo = lista;

   if(ListaVacia(lista)) {
   		printf("Lista vacía\n");
   }else {
      while(nodo) {
         printf("%d -> ", nodo->valor);
         nodo = nodo->siguiente;
    }
     printf("\n");
   }
}
