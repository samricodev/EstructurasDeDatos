#include <stdio.h>
#include <stdlib.h>

//Metodos de ordenamiento 
//Intercambio (Bubble Sort)

int main() {
	
	int aux, i, j, arreglo [5];
	
	for(i = 0; i < 5; i++){
		printf("%d Dame un valor: ",i+1);
		scanf("%d",&arreglo[i]);
	}
	
	//usamos < par asc y < para dsc
	
	for(j = 0; j < 4; j++){
		for(i = 0; i < 4; i++){
			if(arreglo[i] < arreglo[i+1]){
				aux = arreglo[i];
				arreglo[i] = arreglo[i+1];
				arreglo[i+1] = aux;
			}
		}
	}
	
	for(i = 0; i < 5;i++){
		printf("%d\n", arreglo[i]);
	}
	
	return 0;
}
