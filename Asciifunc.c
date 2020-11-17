#include<stdio.h>
#include<stdlib.h>

int FimprAscii (int *valor_ascii, char *caracter){


        if(*valor_ascii >= 48 && *valor_ascii <= 57){
                  printf("El valor ASCII del caracter numerico '%c' es '%d'\n", *caracter, *valor_ascii );
   }else{
                  if(*valor_ascii >= 65 && *valor_ascii <= 90){
                          printf("El valor ASCII del caracter '%c' es la letra '%d'\n", *caracter, *valor_ascii );
            }else{
                          if(*valor_ascii >= 97 && *valor_ascii <= 122){
                                  printf("El valor ASCII del caracter '%c' es la letra '%d'\n", *caracter, *valor_ascii );
                     }else{
                                  printf("El valor ASCII del caracter '%c' es '%d' y pertenece a un caracter especial\n", *caracter, *valor_ascii );
            }
      }
}
}

int main(int num_of_arg, char **ascii_valores)
{
  int valor_ascii;
  int i;
  char caracter;
  int array[num_of_arg];

    for ( i = 1; i < num_of_arg; i ++){
        caracter = (char) atoi(ascii_valores[i]);
        valor_ascii = atoi(ascii_valores[i]);
        FimprAscii (&valor_ascii, &caracter);
    }
	printf("Ingrese un valor\n");
    scanf("%s",&caracter);
return 0;
}
