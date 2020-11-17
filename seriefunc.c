#include<stdio.h>
#include<stdlib.h>

int f_suma_serie(int *elementos_maximos){
  int suma_serie = 0, elem_max = *elementos_maximos;
      printf("La suma de los cuadrados del 1 al %d es:\n\n", *elementos_maximos);
      suma_serie =  (elem_max * (elem_max + 1) * (2 * elem_max + 1))/6;
    printf("SUMA: %d", suma_serie);
}

int f_cuadrados_en_serie(int *elementos_maximos){
	int i;
      printf("\n\nLa serie de los cuadrados del 1 al %d es: \n\n", *elementos_maximos);
      for( i = 1; i <= *elementos_maximos; i ++){
              printf("%d, ", i * i);
      }
      printf("\n\n");
}

int main (int num_of_arg, char **val_for_sq){
  int i;
  int elementos_maximos;

      for(i = 1; i < num_of_arg; i ++){
              elementos_maximos = atoi(val_for_sq[i]);
              f_suma_serie(&elementos_maximos);
              f_cuadrados_en_serie(&elementos_maximos);
      }

return 0;
}
