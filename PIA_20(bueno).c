#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *nombre;
	int matricula;
	int parcial;
	int parcial2;
	int parcial3;
	int parcial4,parcial5,parcial6,parcial7;
	float final;
}Datos;

int main() {
	char linea[200];
	char *token;
	FILE *archivo = fopen ("calificaciones_pia_pe.csv", "r");
	if(archivo==NULL){
		printf("Error al abrir el archivo");
	}
	while(fgets(linea, sizeof(linea), archivo)){
		token=strtok(linea, ",");
		while(token!=NULL){
			printf("%s", token);
			token=strtok(NULL,",");
		}
		printf("\n");
	}
}

void suma_calificaciones(){
	FILE *archivo = fopen ("calificaciones_pia_pe.csv", "r");
	char resultado[100];
	char cad[100];
	char* ptr;
	for(* ptr = cad; *ptr; ++ptr ){
  if( isdigit(*ptr) )
    *ptr = (*ptr!='9')? *ptr+1 : '0';
	}
return 0;
}
