#include <stdio.h>
#include <stdlib.h>

 int main(){

     int elementos_maximos = 100;

     int serie[elementos_maximos];

     int indice;

     for(indice = 1; indice <= elementos_maximos; indice++){

         serie[indice] = indice * indice;

     }

     int sumatoria = 0;

     for(indice = 1; indice <= elementos_maximos; indice++){

         sumatoria = sumatoria + serie[indice];

     }

     printf("Valores sumados: ");

     for(indice = 1; indice <= elementos_maximos; indice++){

         printf("%d, ", serie[indice]);

     }

     printf("\nSumatoria %d", sumatoria);

     int total_calculado = (elementos_maximos*(elementos_maximos + 1)*(2*elementos_maximos + 1))/6;

     printf("\nTotal calculado %d", total_calculado);

     return 0;

 }
