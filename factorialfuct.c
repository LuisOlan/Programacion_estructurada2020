#include <stdio.h>
#include <stdlib.h>

int f_factorial(int number){
          if (number <= 0){
                  return 1;
          } else {
                  return number * f_factorial(number - 1);
          }
}

int main (int arg_cont, char **arg_v){
          int numero = 0;
          int result;
          int i = 0;

          for (i = 1; i < arg_cont; i ++){
                  numero = atoi(arg_v[i]);
                  result = f_factorial(numero);
                  printf("El factorial del numero %d es %d\n", numero, result);
          }
            return 0;
}
