#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define Espacio 1024

typedef struct Calificacion {
	unsigned int AlumnosReprobados;
	int *califAlumnosParcial;
	double Promedio;
} Calificacion;

typedef struct Alumno {
	char Matricula[8];
	int calif[7];
	unsigned int Parciales_Reprobados;
	double Promedio;
} Alumno;

typedef struct Grupo {
	unsigned int AlumnosReprobados;
	int *califAlumnos;
	double Promedio;
} Grupo;

unsigned int lineas_totales(const char* calificaciones_pia_pe) {
	FILE* stream = fopen("calificaciones_pia_pe.csv","r");
	if(!stream) {
		printf("Problema al abrir el archivo %s.\n","calificaciones_pia_pe.csv");
		exit(EXIT_FAILURE);
	}
	unsigned int lineas = 0;
	char texto[Espacio];
	while(fgets(texto,Espacio,stream) != NULL) {
		lineas++;
	}
	fclose(stream);
	return lineas;
}

char** separacion(char* str, const char a_delimitacion) {
	char **_str = NULL;
	size_t contador;
	char *str_tmp = str;
	char *ultima_delimitacion = NULL;
	char delimitacion[2];
	delimitacion[0] = a_delimitacion;
	delimitacion[1] = '\0';

	while(*str_tmp) {
		if(*str_tmp == a_delimitacion) {
			contador++;
			ultima_delimitacion = str_tmp;
		}
		str_tmp++;
	}

	contador += ultima_delimitacion < (str + strlen(str) - 1);
	contador++;

	_str = malloc(sizeof(char*)*(size_t)contador);
	if(_str) {
		size_t idx = 0;
		char* tomado = strtok(str,delimitacion);
		while(tomado) {
			assert(idx < contador);
			*(_str + idx++) = strdup(tomado);
			tomado = strtok(NULL,delimitacion);
		}
		assert(idx == (contador - 1));
		*(_str + idx) = '\0';
	} else {
		printf("No se puede reservar en memoria.\n");
		exit(EXIT_FAILURE);
	}
	return _str;
}

Alumno funcion_registro(char** lug_tomados) {
	size_t i = 0,k = 0;
	Alumno a;

	for(i = 0; *(lug_tomados + i); ++i) {
		if(i > 0) {
			a.calif[k] = (int)strtol(lug_tomados[i],NULL,10);
			k++;
		} else {
			strncpy(a.Matricula,lug_tomados[i],strlen(lug_tomados[i]));
		}
	}
	return a;
}

void load_data(const char* calificaciones_pia_pe, Alumno* Alumnos) {
	FILE* stream = fopen("calificaciones_pia_pe.csv","r");
	if(!stream) {
		printf("Problema al abrir el archivo %s.\n","calificaciones_pia_pe.csv");
		exit(EXIT_FAILURE);
	}
	size_t idx = 0;
	size_t i = 0;
	char texto[Espacio];
	unsigned int lineas = 0;
	char** lug_tomados = NULL;
	while(fgets(texto,Espacio,stream) != NULL) {
		lineas++;
		texto[strcspn(texto,"\n")] = '\0';
		if(lineas > 1) {
			lug_tomados = separacion(texto,',');
			if(lug_tomados) {
				Alumnos[idx] = funcion_registro(lug_tomados);
				for(i = 0; *(lug_tomados + i); ++i) {
					free(*(lug_tomados+i));
				}
				free(lug_tomados);
				lug_tomados = NULL;
			}
			idx++;
		}
	}
	fclose(stream);
}

void funcion_ingreso_info(const char* nombre_doc, Alumno* Alumnos, Calificacion* calificaciones, Grupo g, const size_t tamA, const size_t tamC) {
	FILE* stream = fopen(nombre_doc,"w");
	if(!stream) {
		printf("Problema al abrir el archivo %s.\n",nombre_doc);
		exit(EXIT_FAILURE);
	}
	size_t i = 0, j = 0;
	size_t len = 0;
	fprintf(stream,"Matricula,Parcial 1,Parcial 2,Parcial 3,Parcial 4,Parcial 5,Parcial 6,Parcial 7,Promedio de calificaciones parciales,No Aprobados\n");
	for(i = 0; i < tamA; ++i) {
		len = strlen(Alumnos[i].Matricula);
		for(j = len - 4; j < len; ++j) {
			fputc(Alumnos[i].Matricula[j],stream);
		}
		fprintf(stream,",%d,%d,%d,%d,%d,%d,%d,%d,%u\n",Alumnos[i].calif[0],Alumnos[i].calif[1],Alumnos[i].calif[2],Alumnos[i].calif[3],Alumnos[i].calif[4],Alumnos[i].calif[5],Alumnos[i].calif[6],(int)Alumnos[i].Promedio,Alumnos[i].Parciales_Reprobados);
	}
	fprintf(stream,"Promedios,");
	for(i = 0; i < tamC; ++i) {
		fprintf(stream,"%d,",(int)calificaciones[i].Promedio);
	}
	fprintf(stream,"%d\n",(int)g.Promedio);
	fprintf(stream,"No aprobados,");
	for(i = 0; i < tamC; ++i) {
		fprintf(stream,"%u,",calificaciones[i].AlumnosReprobados);
	}
	fprintf(stream,"%u",g.AlumnosReprobados);
	fclose(stream);
}

double funcion_calcular_Promedios(int* calif, const size_t tam) {
	double prom = 0.0;
	size_t i = 0;
	for(i = 0; i < tam; ++i) {
		prom += calif[i];
	}
	prom /= tam;
	return prom;
}

unsigned int funcion_parciales_reprobados(int* calif,const size_t tam) {
	size_t i = 0;
	unsigned int reprobados = 0;
	for(i = 0; i < tam; ++i) {
		if(calif[i] < 7)
			reprobados++;
	}

	return reprobados;
}



void ini_CalifParcial(unsigned* n_alumR, double* prom, int** califAlumP, const size_t tam, Alumno* Alumnos, const unsigned idx_P) {
	*n_alumR = 0;
	*prom = 0.0;
	*califAlumP = (int*) malloc(sizeof(int)*(size_t)tam);
	if(!(*califAlumP)) {
		printf("No se puede reservar en memoria.\n");
		exit(EXIT_FAILURE);
	}
	size_t k = 0;
	for(k; k < tam; ++k) {
		(*califAlumP)[k] = Alumnos[k].calif[idx_P];
	}
}

double calcular_promParcial(int* califAlumnosP, const size_t tam) {
	double prom = 0.0;
	size_t i = 0;
	for(i; i < tam; ++i) {
		prom += califAlumnosP[i];
	}
	prom /= tam;

	return prom;
}


unsigned int NAlumnosReprobados_P(int* califAlumnosP, const size_t tam) {
	unsigned int reprobados = 0;
	size_t i = 0;
	for(i; i < tam; ++i) {
		if(califAlumnosP[i] < 7)
			reprobados++;
	}

	return reprobados;
}



void ini_califGrupo(Grupo* g, Alumno* Alumnos, const size_t tam) {
	g->califAlumnos = (int*) malloc(sizeof(int)*(size_t)tam);
	if(!g->califAlumnos) {
		printf("No se puede reservar en memoria.\n");
		exit(EXIT_FAILURE);
	}
	size_t i = 0;
	for(i; i < tam; ++i) {
		g->califAlumnos[i] = (int)Alumnos[i].Promedio;
	}
}



double calcular_promGrupo(int* califAlumnos, const size_t tam) {
	size_t i = 0;
	double prom = 0.0;
	for(i; i < tam; ++i) {
		prom += califAlumnos[i];
	}
	prom /= tam;

	return prom;
}



unsigned int NAlumnosReprobados_G(int* califAlumnos, const size_t tam) {
	unsigned int reprobados = 0;
	size_t i = 0;
	for(i; i < tam; ++i) {
		if(califAlumnos[i] < 7)
			reprobados++;
	}

	return reprobados;
}


void print_arrayAlumnos(Alumno* Alumnos,const size_t tam) {
	size_t i = 0, j = 0;
	for(i = 0; i < tam; ++i) {
		printf("Alumno %d\nMatricula: %s\nCalif: ",i+1,Alumnos[i].Matricula);
		for(j = 0; j < 7; ++j) {
			printf("%d ",Alumnos[i].calif[j]);
		}
		printf("\n# de parciales reprobados: %u\nPromedio final: %.2lf",Alumnos[i].Parciales_Reprobados,Alumnos[i].Promedio);
		if(i < tam - 1)
		printf("\n\n");
	}
	printf("\n");
}



void print_arrayCalifP(Calificacion* calificaciones, const size_t tam) {
	size_t i = 0;
	for(i = 0; i < tam; ++i) {
		printf("Parcial %d\nCandidad de alumnos reprobados: %u\nPromedio general del parcial: %.2lf",i+1,calificaciones[i].AlumnosReprobados,calificaciones[i].Promedio);
		if(i < tam - 1)
		printf("\n\n");
	}
	printf("\n");
}



int main() {
	const size_t TAM = lineas_totales("csv.csv") - 1;
	Alumno Alumnos[TAM];
	Calificacion calificacionesP[7];
	Grupo g = {0,NULL,0.0};
	size_t i = 0, j = 0;

	load_data("csv.csv",Alumnos);
	
	for(i = 0; i < TAM; ++i) {
		Alumnos[i].Promedio = round(funcion_calcular_Promedios(Alumnos[i].calif,7));
		Alumnos[i].Parciales_Reprobados = funcion_parciales_reprobados(Alumnos[i].calif,7);
	}
	for(i = 0; i < 7; ++i) {
		ini_CalifParcial(&calificacionesP[i].AlumnosReprobados,&calificacionesP[i].Promedio,&calificacionesP[i].califAlumnosParcial,TAM,Alumnos,i);
		calificacionesP[i].Promedio = round(calcular_promParcial(calificacionesP[i].califAlumnosParcial,TAM));
		calificacionesP[i].AlumnosReprobados = funcion_parciales_reprobados(calificacionesP[i].califAlumnosParcial,TAM);
	}


	ini_califGrupo(&g,Alumnos,TAM);
	g.Promedio = round(calcular_promGrupo(g.califAlumnos,TAM));
	g.AlumnosReprobados = NAlumnosReprobados_G(g.califAlumnos,TAM);
	funcion_ingreso_info("calificaciones_prueba.csv",Alumnos,calificacionesP,g,TAM,7);
	print_arrayAlumnos(Alumnos,TAM);
	printf("\n");
	print_arrayCalifP(calificacionesP,7);
	printf("\nEl promedio del Grupo es de: %.2lf\nEl total de alumnos reprobados del grupo es de %u\n",g.Promedio,g.AlumnosReprobados);
	for(i = 0; i < 7; ++i) {
		free(calificacionesP[i].califAlumnosParcial);
	}
	free(g.califAlumnos);

	return 0;
}
