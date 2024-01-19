#include <iostream>
using namespace std;

class nodo {
   public:
    nodo(int v, nodo *sig = NULL) {
       valor = v;
       siguiente = sig;
    }
   private:
    int valor;
    nodo *siguiente;
   friend class cola;
};

typedef nodo *pnodo;

class cola {
   public:
    cola() : ultimo(NULL), primero(NULL) {}
    ~cola();
    void Anadir(int v);
    int Leer();
   private:
    pnodo primero, ultimo;
};

cola::~cola() {
   while(primero) Leer();
}

void cola::Anadir(int v) {
   pnodo nuevo;
   /* Crear un nodo nuevo */
   nuevo = new nodo(v);
   /* Si la cola no estaba vac�a, a�adimos el nuevo a continuaci�n de ultimo */
   if(ultimo) ultimo->siguiente = nuevo;
   /* Ahora, el �ltimo elemento de la cola es el nuevo nodo */
   ultimo = nuevo;
   /* Si primero es NULL, la cola estaba vac�a, ahora primero apuntar� tambi�n al nuevo nodo */
   if(!primero) primero = nuevo;
}

int cola::Leer() {
   pnodo nodo; /* variable auxiliar para manipular nodo */
   int v;      /* variable auxiliar para retorno */
   /* Nodo apunta al primer elemento de la pila */
   nodo = primero;
   if(!nodo) return 0; /* Si no hay nodos en la pila retornamos 0 */
   /* Asignamos a primero la direcci�n del segundo nodo */
   primero = nodo->siguiente;
   /* Guardamos el valor de retorno */
   v = nodo->valor;
   /* Borrar el nodo */
   delete nodo;
   /* Si la cola qued� vac�a, ultimo debe ser NULL tambi�n*/
   if(!primero) ultimo = NULL;
   return v;
}

int main() {
	cola Cola;
	int dato, n;
	cout<<"Nodos a encolar: ";
	cin>>n;
	for(int i = 0; i < n;i++){
		cout<<i+1<<".- Agrega un nodo con el valor: ";
		cin>>dato;
		Cola.Anadir(dato);
	}
	for(int j = 0; j < n-1;j++){
		cout<<"Valor: "<<Cola.Leer()<<" ha sido eliminado"<<endl;
	}
	return 0;
}
