#include <stdio.h>
#define asc 1
#define des 0

typedef struct nodo {
   char *color;
   struct nodo *siguiente;
   struct nodo *anterior;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

/* Funciones con listas: */
void Insertar(Lista *l, char *color);
void Borrar(Lista *l, char *color);
void BorrarLista(Lista *lista);
void MostrarLista(Lista l, int orden);

int main() {
   Lista lista = NULL;
	
	printf("Agregamos nodos\n");
   	Insertar(&lista, "azul");
   	Insertar(&lista, "gris");
   	Insertar(&lista, "rojo");
   	Insertar(&lista, "morado");
   	Insertar(&lista, "negro");

   	MostrarLista(lista, asc);
   	
	printf("\nBorramos nodos\n");
   	Borrar(&lista, "rojo");
   	Borrar(&lista, "negro");
   
   	MostrarLista(lista, des);

   	BorrarLista(&lista);

   	return 0;
}

void Insertar(Lista *lista, char *color) {
   pNodo nuevo, actual;

   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->color = color;

   actual = *lista;
   if(actual) while(actual->anterior) actual = actual->anterior;
   if(!actual || actual->color > color){
      nuevo->siguiente = actual;
      nuevo->anterior = NULL;
      if(actual) actual->anterior = nuevo;
      if(!*lista) *lista = nuevo;
   }
   else {
      while(actual->siguiente && actual->siguiente->color <= color)
    		actual = actual->siguiente;
      		nuevo->siguiente = actual->siguiente;
      		actual->siguiente = nuevo;
      		nuevo->anterior = actual;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
   }
}

void Borrar(Lista *lista, char *color) {
   pNodo nodo;

   /* Buscar el nodo de valor v */
   nodo = *lista;
   while(nodo && nodo->color < color) nodo = nodo->siguiente;
   while(nodo && nodo->color > color) nodo = nodo->anterior;

   /* El valor v no está en la lista */
   if(!nodo || nodo->color != color) return;

   /* Borrar el nodo */
   /* Si lista apunta al nodo que queremos borrar, apuntar a otro */
   if(nodo == *lista)
     if(nodo->anterior) *lista = nodo->anterior;
     else *lista = nodo->siguiente;

   if(nodo->anterior) /* no es el primer elemento */
      nodo->anterior->siguiente = nodo->siguiente;
   if(nodo->siguiente) /* no es el último nodo */
      nodo->siguiente->anterior = nodo->anterior;
   free(nodo);
}

void BorrarLista(Lista *lista) {
   pNodo nodo, actual;

   actual = *lista;
   while(actual->anterior) actual = actual->anterior;

   while(actual) {
      nodo = actual;
      actual = actual->siguiente;
      free(nodo);
   }
   *lista = NULL;
}

void MostrarLista(Lista lista, int orden) {
   pNodo nodo = lista;

   if(!lista) printf("Lista vacía");

   nodo = lista;
   if(orden == asc) {
      while(nodo->anterior) nodo = nodo->anterior;
      printf("\nOrden ascendente.");
      while(nodo) {
         printf("\n%s", nodo->color);
         nodo = nodo->siguiente;
      }
   }
   else {
      while(nodo->siguiente) nodo = nodo->siguiente;
      printf("\nOrden descendente.");
      while(nodo) {
         printf("\n%s", nodo->color);
         nodo = nodo->anterior;
      }
   }

   printf("\n");
}

