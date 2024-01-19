#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

struct Nodo{
	int dato;
	struct Nodo *izq;
	struct Nodo *der;
	struct Nodo *padre;
};

//Prototipos
Nodo *crearNodo(int n, Nodo *padre);
void insertar(Nodo *&arbol, Nodo *padre, int n);
void mostrarArbol(Nodo *arbol, int contador);
bool busqueda(Nodo *arbol, int n);
void preOrden(Nodo *arbol);
void posOrden(Nodo *arbol);
void inOrden(Nodo *arbol);
void eliminar(Nodo *arbol, int n);
void eliminarNodo(Nodo *nodoEliminar);
void reemplazar(Nodo *arbol, Nodo *nuevo);
void destruirNodo(Nodo *nodoDestruir);
Nodo *minimo(Nodo *arbol);
void menu();
Nodo *arbol = NULL;

int main(int argc, char** argv) {
	
	menu();
	
	getch();
	return 0;
}

//menu
void menu(){
	int dato, opcion, cont=0;
	
	do{
		cout<<"\t.:Menu:."<<endl;
		cout<<"1. Insertar Nodo"<<endl;
		cout<<"2. Mostrar Arbol"<<endl;
		cout<<"3. Buscar Nodo"<<endl;
		cout<<"4. Pre Orden"<<endl;
		cout<<"5. In Orden"<<endl;
		cout<<"6. Pos Orden"<<endl;
		cout<<"7. Eliminar nodo"<<endl;
		cout<<"8. Salir"<<endl;
		cout<<"Opcion: ";
		cin>>opcion;
		
		switch(opcion){
			case 1:
				cout<<"\nDigite un numero: ";
				cin>>dato;
				insertar(arbol,NULL,dato);
				cout<<"\n";
				system("pause");
				break;
			case 2:
				cout<<"\Monstando arbol\n\n";
				mostrarArbol(arbol,cont);
				cout<<"\n";
				system("pause");
				break;
			case 3:
				cout<<"\nDigita el nodo a buscar: ";
				cin>>dato;
				if(busqueda(arbol, dato)){
					cout<<"\nElemento "<<dato<<" ha sido encontrado\n";
				} else{
					cout<<"\nElemnto no encontrado";
				}
				cout<<"\n";
				system("pause");
				break;
			case 4:
				cout<<"\nMostrar en Pre Orden\n";
				preOrden(arbol);
				cout<<"\n";
				system("pause");
				break;
			case 5:
				cout<<"\nMostrar en In Orden\n";
				inOrden(arbol);
				cout<<"\n";
				system("pause");
				break;
			case 6:
				cout<<"\nMostrar en Pos Orden\n";
				posOrden(arbol);
				cout<<"\n";
				system("pause");
				break;
			case 7:
				cout<<"\nDigita el nodo a eliminar: ";
				cin>>dato;
				eliminar(arbol, dato);
				cout<<"\n";
				system("pause");
				break;
			case 8:
				cout<<"\nFin del programa";
				return;
			default:
				cout<<"Opcion Invalida";
		}
		system("cls");
	}while(opcion != 8);
}

//Crear nodo
Nodo *crearNodo(int n, Nodo *padre){
	Nodo *nuevoNodo = new Nodo();
	
	nuevoNodo->dato = n;
	nuevoNodo->der = NULL;
	nuevoNodo->izq = NULL;
	nuevoNodo->padre = padre;
	
	return nuevoNodo;
}

//Insertar nodos
void insertar(Nodo *&arbol, Nodo *padre, int n){
	if(arbol == NULL){
		Nodo *nuevoNodo = crearNodo(n,padre);
		arbol = nuevoNodo;
	} else{
		if(n < arbol->dato){
			insertar(arbol->izq, arbol, n);
		} else{
			insertar(arbol->der, arbol, n);
		}
	}
}

//Mostrar
void mostrarArbol(Nodo *arbol, int cont){
	if(arbol == NULL){
		return;
	}else{
		mostrarArbol(arbol->der, cont+1);
		for(int i = 0; i<cont;i++){
			cout<< "   ";
		}
		cout<<arbol->dato<<endl;
		mostrarArbol(arbol->izq,cont+1);
	}
}

//Mostrar en pre orden
void preOrden(Nodo *arbol){
	if(arbol == NULL){
		return;
	}else{
		cout<<arbol->dato<<" - ";
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}
}

//Mostrar en pos orden
void posOrden(Nodo *arbol){
	if(arbol == NULL){
		return;
	}else{
		posOrden(arbol->izq);
		posOrden(arbol->der);
		cout<<arbol->dato<<" - ";
	}
}

//Mostrar en in orden
void inOrden(Nodo *arbol){
	if(arbol == NULL){
		return;
	} else{
		inOrden(arbol->izq);
		cout<<arbol->dato<<" - ";
		inOrden(arbol->der);
	}
}

//Buscar Nodo
bool busqueda(Nodo *arbol, int n){
	if(arbol == NULL){
		return false;
	}else if(arbol->dato == n){
		return true;
	}else if(n < arbol->dato){
		return busqueda(arbol->izq, n);
	} else{
		return busqueda(arbol->der, n);
	}
}

//Eliminar nodo
void eliminar(Nodo *arbol, int n){
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

//Encontrar el nodo mas izq
Nodo *minimo(Nodo *arbol){
	if(arbol == NULL){
		return NULL;
	} 
	if(arbol->izq){
		return minimo(arbol->izq);
	} else{
		return arbol;
	}
}

//Reemplazar el hijo del nodo a borrar
void reemplazar(Nodo *arbol, Nodo *nuevo){
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

//Destruimos el nodo
void destruirNodo(Nodo *nodo){
	nodo->izq = NULL;
	nodo->der = NULL;
	
	delete(nodo);
}

//Elimnar el nodo encontrado
void eliminarNodo(Nodo *nodoEliminar){
	if(nodoEliminar->izq && nodoEliminar->der){
		Nodo *menor = minimo(nodoEliminar->der);
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

