#include <stdio.h>
#include <stdlib.h>

int main() {
	char n;
	printf("Ingresa un caracter: \n");
	scanf("%c",&n);
	if(n>=66 && n<=90 || n>=97 && n<=122 || n>=164 && n<=165){
		if(n==65 || n==69 || n==73 || n==79 || n==85 || n==97 || n==101 || n==105 || n==111 || n==117)
			printf("La letra %c es vocal",n);
			else
			printf("La letra %c no es vocal",n);
		}
	else{
		printf("El valor no es una letra");
	}
	return 0;
}
