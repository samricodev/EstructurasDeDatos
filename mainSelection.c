#include <stdio.h>
#include <stdlib.h>
//Metodo de ordenamiento Algoritmo de Seleccion
int main(int argc, char *argv[]) {
	
	int arr[] = {4,5,3,6,1,7,8};
	int tam = 7;
	printf("Entrada: ");
	imprimir(arr, tam);
	selection(arr, tam);
	
	return 0;
}

void selection(int *vector, int tam){
	int actual, min, j, i, temp;
	for(actual = 0; actual < tam; actual++){
		min = actual;
		for(j = actual; j < tam-1; j++){
			if(vector[j] < vector[min]){
				min = j;
				temp = vector[actual];
				vector[actual] = vector[min];
				vector[min] = temp;
			}
		}
	}
	
	printf("\nSeleccion: ");
	imprimir(vector, tam);
}
  
void imprimir(int vector[], int tam){
	int i;
	
	for(i = 0;i < tam; i++){
		printf("%d,",vector[i]);
	}
}
