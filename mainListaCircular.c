#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int valor;
	struct nodo *siguiente;
}tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

void Insertar(Lista *lista, int v);
void Borrar(Lista *lista, int v);
void BorrarLista(Lista *lista);
void MostrarLista(Lista lista);

int main(int argc, char *argv[]) {
	
	Lista *lista = NULL;
	int i,j,v,n,borrar;
	
	printf("Nodos a crear: ");
	scanf("%d",&n);
	
	for(i = 0;i < n; i++){
		printf("Ingresa el valor del nodo: ");
		scanf("%d",&v);
		Insertar(&lista, v);
	}
	
	MostrarLista(lista);
	
	printf("Nodos a borrar: ");
	scanf("%d",&borrar);
	
	for(j = 0; j < borrar; j++){
		printf("Ingresa el valor del nodo a borrar: ");
		scanf("%d",&v);
		Borrar(&lista, v);
	}
	
	MostrarLista(lista);
	
	BorrarLista(&lista);
	
	return 0;
}

void Insertar(Lista *lista, int v){
	pNodo nodo;
	nodo = (pNodo)malloc(sizeof(tipoNodo));
	nodo->valor = v;
	
	if(*lista == NULL) *lista = nodo;
	else nodo->siguiente = (*lista)->siguiente;
	
	(*lista)->siguiente = nodo;
}

void Borrar(Lista *lista, int v){
	pNodo nodo;
	nodo = *lista;
	
	do{
		if((*lista)->siguiente->valor != v) *lista = (*lista)->siguiente;
	} while((*lista)->siguiente->valor != v && *lista != nodo);
	if((*lista)->siguiente->valor == v){
		if(*lista == (*lista)->siguiente){
			free(*lista);
			*lista = NULL;
		} else{
			nodo = (*lista)->siguiente;
			(*lista)->siguiente = nodo->siguiente;
			free(nodo);
		}
	}
}

void BorrarLista(Lista *lista){
	pNodo nodo;
	
	while((*lista)->siguiente != *lista){
		nodo = (*lista)->siguiente;
		(*lista)->siguiente = nodo->siguiente;
		free(nodo);
	}
	
	free(*lista);
	*lista = NULL;	
}

void MostrarLista(Lista lista){
	pNodo nodo = lista;
	
	do{
		printf("%d -> ", nodo->valor);
		nodo = nodo->siguiente;
	}while(nodo != lista);
	printf("\n");
}
