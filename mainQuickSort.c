#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	int arr[] = {5,2,7,3,8,1,9};
	int tam = 7;
	printf("Entrada: ");
	imprimir(arr, tam);
	quick_sort(arr, tam);
	printf("\nQuicksort: ");
	imprimir(arr, tam);
   	
	return 0;
}

void quick_sort (int *vector, int tam) {
    int pared, actual, pivote, tmp;

	if (tam < 2) return;
    // el elemento de pivote es el ultimo
    pivote = vector[tam - 1];
    pared  = actual = 0;
    while (actual<tam) {
        if (vector[actual] <= pivote) {
            if (pared != actual) {
                tmp=vector[actual];
                vector[actual]=vector[pared];
                vector[pared]=tmp;              
            }
            pared ++;
        }
        actual ++;
    }
    
    quick_sort(vector, pared - 1);
    quick_sort(vector + pared - 1, tam - pared + 1);
    
}

void imprimir(int arr[], int tam){
	
	int i;
	
	for(i = 0; i < tam; i++){
    	printf("%d, ",arr[i]);
	}
}

