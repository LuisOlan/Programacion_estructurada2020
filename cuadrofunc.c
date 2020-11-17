#include <stdio.h>
#include <stdlib.h>

int funcion_ImprimeCuadro (int *, int *);

int main (int no_d_arg, char **valores){
        int largo, alto;
        largo = atoi(valores[1]);
        alto = atoi(valores[2]);
        funcion_ImprimeCuadro (&largo, &alto);
}

int funcion_ImprimeCuadro (int * largo, int * alto){
  char vertical = '|', horizontal = '-', esquina = '+';

  int alto_contador, contador_horizontal;
  printf("\n\n");

  for (alto_contador = 0; alto_contador < (*alto); alto_contador ++){
        for (contador_horizontal = 0; contador_horizontal < (*largo); contador_horizontal ++){
            if (alto_contador == 0 || alto_contador == (*alto) - 1){
                if (contador_horizontal == 0 || contador_horizontal == (*largo) - 1){
                    printf("%c", esquina);
    } else {
                    printf("%c", horizontal); }
} else {
                if (contador_horizontal == 0 || contador_horizontal == (*largo) - 1){
                    printf("%c", vertical);
     } else {
                    printf(" "); }
}
}
printf("\n" );
}
}
