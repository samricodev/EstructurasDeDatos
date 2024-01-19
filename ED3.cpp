#include <stdio.h>
#include <Math.h>
int main(){
	int culitos [5];
	int sum = 0;
	double parit, pgeom = 1;
	for(int i = 0; i < 5;i++){
		printf("Dame un numero alv: ");
		scanf("%d",&culitos[i]);
		sum += culitos[i];
		pgeom = pgeom * culitos[i];
	}
	
	for(int i = 0; i < 5 ;i++){
		printf("%d\n",culitos[i]);
	}
	
	parit = 1 * sum / 5;
	pgeom = pow(pgeom, 1/5);
	printf("La suma es: %d\n", sum);
	printf("La pote es: %f\n", pgeom);
	printf("La pariedad es: %f\n", parit);

	return 0;
}
