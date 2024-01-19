#include <iostream>
#include <cctype>
//Lista Doblemente Enlazada en C++
using namespace std;


typedef struct Nodo{
	string color;
	struct Nodo *siguiente;
	struct Nodo *anterior;
}tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

void Insertar(Lista *lista, string color);
//void Borrar(Lista *lista, string color);
void BorrarLista(Lista *lista);
void MostrarLista(Lista lista, int orden);

int main(int argc, char** argv) {
 
    Lista lista = NULL;
	int i, j, n,asc = 1, des = 0;
	string color;
	
	cout<<"Digita los nodos a crear: ";
	cin>>n;
	
	for(i = 0; i < n; i++){
		cout<<"Digita el color: ";
		cin>>color;
		Insertar(&lista,color);
	}
	
	MostrarLista(lista, asc);
	
	MostrarLista(lista, des);
	
	BorrarLista(&lista);
 
	return 0;
}

void Insertar(Lista *lista, string color){
	pNodo nuevo, actual;
	nuevo = new Nodo;
	actual = *lista;
	if(actual) while(actual->anterior) actual = actual->anterior;
 
	if(!actual || actual->color > color) {
		nuevo->siguiente = actual;
		nuevo->anterior = NULL;
		if(actual) actual->anterior = nuevo;
		if(!*lista) *lista = nuevo;
	}else {
		while(actual->siguiente && actual->siguiente->color <= color)
		actual = actual->siguiente;
 
		nuevo->siguiente = actual->siguiente;
		actual->siguiente = nuevo;
		nuevo->anterior = actual;
		if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
	}
}

void BorrarLista(Lista *lista) {
   pNodo nodo, actual;
 
   actual = *lista;
   while(actual->anterior) actual = actual->anterior;
 
   while(actual) {
      nodo = actual;
      actual = actual->siguiente;
      delete(nodo);
   }
   *lista = NULL;
}

void MostrarLista(Lista lista, int orden) {
   pNodo nodo = lista;
 
   if(!lista) cout << "\nLista vacía";
 
   nodo = lista;
   if(orden == 1) {
	while(nodo->anterior) nodo = nodo->anterior;
      cout << "\nOrden ascendente: ";
      cout << "\n";
      while(nodo) {
         cout << nodo->color;
         nodo = nodo->siguiente;
      }
   } else {
      	while(nodo->siguiente) nodo = nodo->siguiente;
      	cout << "\nOrden descendente: ";
      	cout << "\n";
      	while(nodo) {
        	cout << nodo->color;
        	nodo = nodo->anterior;
      }
   }
   
   cout<< endl;
}

