#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

enum {IZQUIERDO, DERECHO};
//Estructuras y tipos
typedef struct _nodo {
   int dato;
   int FE;
   struct _nodo *derecho;
   struct _nodo *izquierdo;
   struct _nodo *padre;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;
//Funciones con �rboles:
//Insertar en �rbol ordenado:
void Insertar(Arbol *a, int dat);
// Borrar un elemento:
void Borrar(Arbol *a, int dat);
//Funci�n de b�squeda:
int Buscar(Arbol a, int dat);
// Comprobar si el �rbol est� vac�o:
int Vacio(Arbol r);
//Comprobar si es un nodo hoja:
int EsHoja(pNodo r);
// Contar n�mero de nodos:
int NumeroNodos(Arbol a, int* c);
//Calcular la altura de un �rbol:
int AlturaArbol(Arbol a, int* altura);
//Calcular altura de un dato:
int Altura(Arbol a, int dat);
//Aplicar una funci�n a cada elemento del �rbol
void InOrden(Arbol, void (*func)(int*));
void PreOrden(Arbol, void (*func)(int*));
void PostOrden(Arbol, void (*func)(int*));
// Funciones de equilibrado:
void Equilibrar(Arbol *raiz, pNodo nodo, int, int);
void RSI(Arbol *raiz, pNodo nodo);
void RSD(Arbol *raiz, pNodo nodo);
void RDI(Arbol *raiz, pNodo nodo);
void RDD(Arbol *raiz, pNodo nodo);
/* Funciones auxiliares: */
void Podar(Arbol *a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);
void Mostrar(int *d);

int main(){
   Arbol ArbolInt=NULL;
   int altura;
   int nnodos;

   /* Inserci�n de nodos en �rbol: */
   Insertar(&ArbolInt, 10);
   Insertar(&ArbolInt, 5);
   Insertar(&ArbolInt, 12);
   Insertar(&ArbolInt, 4);
   Insertar(&ArbolInt, 7);
   Insertar(&ArbolInt, 3);
   Insertar(&ArbolInt, 6);
   Insertar(&ArbolInt, 9);
   Insertar(&ArbolInt, 8);
   Insertar(&ArbolInt, 11);
   Insertar(&ArbolInt, 14);
   Insertar(&ArbolInt, 13);
   Insertar(&ArbolInt, 2);
   Insertar(&ArbolInt, 1);
   Insertar(&ArbolInt, 15);
   Insertar(&ArbolInt, 10);
   Insertar(&ArbolInt, 17);
   Insertar(&ArbolInt, 18);
   Insertar(&ArbolInt, 16);

   printf("Altura de arbol %d\n", AlturaArbol(ArbolInt, &altura));

   /* Mostrar el �rbol en tres ordenes distintos: */
   printf("InOrden: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   printf("PreOrden: ");
   PreOrden(ArbolInt, Mostrar);
   printf("\n");
   printf("PostOrden: ");
   PostOrden(ArbolInt, Mostrar);
   printf("\n");

   /* Borraremos algunos elementos: */
   printf("N nodos: %d\n", NumeroNodos(ArbolInt, &nnodos));
   Borrar(&ArbolInt, 5);
   printf("Borrar 5: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 8);
   printf("Borrar 8: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 15);
   printf("Borrar 15: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 245);
   printf("Borrar 245: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 4);
   printf("Borrar 4: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");
   Borrar(&ArbolInt, 17);
   printf("Borrar 17: ");
   InOrden(ArbolInt, Mostrar);
   printf("\n");

   /* Veamos algunos par�metros */
   printf("N nodos: %d\n", NumeroNodos(ArbolInt, &nnodos));
   printf("Altura de 1 %d\n", Altura(ArbolInt, 1));
   printf("Altura de 10 %d\n", Altura(ArbolInt, 10));
   printf("Altura de arbol %d\n", AlturaArbol(ArbolInt, &altura));

   /* Liberar memoria asociada al �rbol: */
   Podar(&ArbolInt);
   system("PAUSE");
   return 0;
}

/* Poda: borrar todos los nodos a partir de uno, incluido */
void Podar(Arbol *a)
{
   /* Algoritmo recursivo, recorrido en postorden */
   if(*a) {
      Podar(&(*a)->izquierdo); /* Podar izquierdo */
      Podar(&(*a)->derecho);   /* Podar derecho */
      free(*a);                /* Eliminar nodo */
      *a = NULL;
   }
}

/* Insertar un dato en el �rbol ABB */
void Insertar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual = *a;

   /* Buscar el dato en el �rbol, manteniendo un puntero al nodo padre */
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }

   /* Si se ha encontrado el elemento, regresar sin insertar */
   if(!Vacio(actual)) return;
   /* Si padre es NULL, entonces el �rbol estaba vac�o, el nuevo nodo ser�
      el nodo raiz */
   if(Vacio(padre)) {
      *a = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
      (*a)->padre = NULL;
      (*a)->FE = 0;
   }
   /* Si el dato es menor que el que contiene el nodo padre, lo insertamos
      en la rama izquierda */
   else if(dat < padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->FE = 0;
      Equilibrar(a, padre, IZQUIERDO, TRUE);
   }
   /* Si el dato es mayor que el que contiene el nodo padre, lo insertamos
      en la rama derecha */
   else if(dat > padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->FE = 0;
      Equilibrar(a, padre, DERECHO, TRUE);
  }
}

/* Equilibrar �rbol AVL partiendo del nodo nuevo */
void Equilibrar(Arbol *a, pNodo nodo, int rama, int nuevo)
{
   int salir = FALSE;

   /* Recorrer camino inverso actualizando valores de FE: */
   while(nodo && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--; /* Depende de si a�adimos ... */
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; /* ... o borramos */
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = TRUE; /* La altura de las rama que
                                         empieza en nodo no ha variado,
                                         salir de Equilibrar */
      else if(nodo->FE == -2) { /* Rotar a derechas y salir: */
         if(nodo->izquierdo->FE == 1) RDD(a, nodo); /* Rotaci�n doble  */
         else RSD(a, nodo);                         /* Rotaci�n simple */
         salir = TRUE;
      }
      else if(nodo->FE == 2) {  /* Rotar a izquierdas y salir: */
         if(nodo->derecho->FE == -1) RDI(a, nodo); /* Rotaci�n doble  */
         else RSI(a, nodo);                        /* Rotaci�n simple */
         salir = TRUE;
      }
      if(nodo->padre)
         if(nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
      nodo = nodo->padre; /* Calcular FE, siguiente nodo del camino. */
   }
}

/* Rotaci�n doble a derechas */
void RDD(Arbol *raiz, Arbol nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo R = Q->derecho;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *raiz = R;

   /* Reconstruir �rbol: */
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;

   /* Reasignar padres: */
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   /* Ajustar valores de FE: */
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}

/* Rotaci�n doble a izquierdas */
void RDI(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo R = Q->izquierdo;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *a = R;

   /* Reconstruir �rbol: */
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;

   /* Reasignar padres: */
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   /* Ajustar valores de FE: */
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

/* Rotaci�n simple a derechas */
void RSD(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo B = Q->derecho;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *a = Q;

   /* Reconstruir �rbol: */
   P->izquierdo = B;
   Q->derecho = P;

   /* Reasignar padres: */
   P->padre = Q;
if(B) B->padre = P;
   Q->padre = Padre;

   /* Ajustar valores de FE: */
   P->FE = 0;
   Q->FE = 0;
}

/* Rotaci�n simple a izquierdas */
void RSI(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo B = Q->izquierdo;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *a = Q;

   /* Reconstruir �rbol: */
   P->derecho = B;
   Q->izquierdo = P;

   /* Reasignar padres: */
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   /* Ajustar valores de FE: */
   P->FE = 0;
   Q->FE = 0;
}

/* Eliminar un elemento de un �rbol ABB */
void Borrar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual;
   pNodo nodo;
   int aux;

   actual = *a;
   /* Mientras sea posible que el valor est� en el �rbol */
   while(!Vacio(actual)) {
      if(dat == actual->dato) { /* Si el valor est� en el nodo actual */
         if(EsHoja(actual)) { /* Y si adem�s es un nodo hoja: lo borramos */
            if(padre) /* Si tiene padre (no es el nodo raiz) */
               /* Anulamos el puntero que le hace referencia */
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            free(actual); /* Borrar el nodo */
            actual = NULL;
            /* El nodo padre del actual puede ser ahora un nodo hoja, por lo
               tanto su FE es cero, pero debemos seguir el camino a partir de
               su padre, si existe. */
            if((padre->derecho == actual && padre->FE == 1) ||
               (padre->izquierdo == actual && padre->FE == -1)) {
               padre->FE = 0;
               actual = padre;
               padre = actual->padre;
            }
            if(padre)
               if(padre->derecho == actual) Equilibrar(a, padre, DERECHO, FALSE);
               else                         Equilibrar(a, padre, IZQUIERDO, FALSE);
            return;
         }
         else { /* Si el valor est� en el nodo actual, pero no es hoja */
            padre = actual;
            /* Buscar nodo m�s izquierdo de rama derecha */
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            /* O buscar nodo m�s derecho de rama izquierda */
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            /* Intercambiar valores de no a borrar u nodo encontrado
               y continuar, cerrando el bucle. El nodo encontrado no tiene
               por qu� ser un nodo hoja, cerrando el bucle nos aseguramos
               de que s�lo se eliminan nodos hoja. */
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { /* Todav�a no hemos encontrado el valor, seguir busc�ndolo */
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
}

/* Recorrido de �rbol en inorden, aplicamos la funci�n func, que tiene
   el prototipo:
   void func(int*);
*/
void InOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) InOrden(a->izquierdo, func);
   func(&(a->dato));
   if(a->derecho) InOrden(a->derecho, func);
}

/* Recorrido de �rbol en preorden, aplicamos la funci�n func, que tiene
   el prototipo:
   void func(int*);
*/
void PreOrden(Arbol a, void (*func)(int*))
{
   func(&a->dato);
   if(a->izquierdo) PreOrden(a->izquierdo, func);
   if(a->derecho) PreOrden(a->derecho, func);
}

/* Recorrido de �rbol en postorden, aplicamos la funci�n func, que tiene
   el prototipo:
   void func(int*);
*/
void PostOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) PostOrden(a->izquierdo, func);
   if(a->derecho) PostOrden(a->derecho, func);
   func(&a->dato);
}

/* Buscar un valor en el �rbol */
int Buscar(Arbol a, int dat)
{
   pNodo actual = a;

   /* Todav�a puede aparecer, ya que quedan nodos por mirar */
   while(!Vacio(actual)) {
      if(dat == actual->dato) return TRUE; /* dato encontrado */
      else if(dat < actual->dato) actual = actual->izquierdo; /* Seguir */
      else if(dat > actual->dato) actual = actual->derecho;
   }
   return FALSE; /* No est� en �rbol */
}

/* Calcular la altura del nodo que contiene el dato dat */
int Altura(Arbol a, int dat)
{
   int altura = 0;
   pNodo actual = a;

   /* Todav�a puede aparecer, ya que quedan nodos por mirar */
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; /* encontrado: devolver altura */
      else {
         altura++; /* Incrementamos la altura, seguimos buscando */
         if(dat < actual->dato) actual = actual->izquierdo;
         else if(dat > actual->dato) actual = actual->derecho;
      }
   }
   return -1; /* No est� en �rbol, devolver -1 */
}

/* Contar el n�mero de nodos */
int NumeroNodos(Arbol a, int *contador)
{
   *contador = 0;

   auxContador(a, contador); /* Funci�n auxiliar */
   return *contador;
}

/* Funci�n auxiliar para contar nodos. Funci�n recursiva de recorrido en
   preorden, el proceso es aumentar el contador */
void auxContador(Arbol nodo, int *c)
{
   (*c)++; /* Otro nodo */
   /* Continuar recorrido */
   if(nodo->izquierdo) auxContador(nodo->izquierdo, c);
   if(nodo->derecho)   auxContador(nodo->derecho, c);
}

/* Calcular la altura del �rbol, que es la altura del nodo de mayor altura. */
int AlturaArbol(Arbol a, int *altura)
{
   *altura = 0;

   auxAltura(a, 0, altura); /* Funci�n auxiliar */
   return *altura;
}

/* Funci�n auxiliar para calcular altura. Funci�n recursiva de recorrido en
   postorden, el proceso es actualizar la altura s�lo en nodos hojas de mayor
   altura de la m�xima actual */
void auxAltura(pNodo nodo, int a, int *altura)
{
   /* Recorrido postorden */
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1, altura);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1, altura);
   /* Proceso, si es un nodo hoja, y su altura es mayor que la actual del
      �rbol, actualizamos la altura actual del �rbol */
   if(EsHoja(nodo) && a > *altura) *altura = a;
}

/* Comprobar si un �rbol es vac�o */
int Vacio(Arbol r)
{
   return r==NULL;
}

/* Comprobar si un nodo es hoja */
int EsHoja(pNodo r)
{
   return !r->derecho && !r->izquierdo;
}

/* Funci�n de prueba para recorridos del �rbol */
void Mostrar(int *d)
{
   printf("%d, ", *d);
}

