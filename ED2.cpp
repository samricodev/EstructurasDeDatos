#include <stdio.h>
#include <stdlib.h>
int i, n, *x, *p = NULL;
int main(int argc, char *argv[]){
	
	printf("Cuantos valores vas a introducir:");
	scanf("%d",&n);
	
	x = (int*)malloc(n * sizeof(int));
	for(i = 0; i < n;i++){
		printf("Dame el elemento numero %d:",i +1);
		scanf("%d",x+i);
	}
	
	for(i = 0; i < n;i++){
		printf("El elemento numero %d es %d\n",i+1,*(x+i));
	}
	
	return 0;
}
