#include <stdio.h>
#include <stdlib.h>

int main() {
	int filas=14,columnas=20,i,j;
	for(i=0; i<filas; i++) {
    	for(j=0; j<columnas; j++) {
        	if (i==0 || i==filas-1) {
            	printf("*");
        	}	
        	else if(j==0 || j==columnas-1) {
            	printf("*");
        	}
        	else {
            	printf(" ");
        	}
        	printf(" ");
    	}
    	printf("\n");
	}
	return 0;
}
