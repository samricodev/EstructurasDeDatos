#include <stdio.h>
#include <stdlib.h>

//Metodo de ordenamiento Algoritmo de Insercion

int main(int argc, char *argv[]) {
	int arr[]={4,3,5,6,2};
	int tam = 5;
	printf("Entrada: ");
	imprimir(arr,tam);
	ordenacion(arr, tam);
	return 0;
}

void ordenacion(int *a, int tam){
	int i, j, aux;
	for(i = 1; i < tam;i++){
		j = i;
		aux = a[i];
		while(j > 0 && aux < a[j-1]){
			a[j] = a[j - 1];
			j--;
		}
		a[j] = aux;
	}
	
	printf("\nInsercion: ");
	imprimir(a,tam);
}

void imprimir(int a[], int tam){
	int i;
	for(i = 0; i < tam; i++){
		printf("%d,",a[i]);
	}
}
