#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MAXLONG_BUFFER 1024

typedef struct{
	char *nombre;
	int matricula;
	int parcial;
	int parcial2;
	int parcial3;
	int parcial4,parcial5,parcial6,parcial7;
	float final;
}Datos;

int guardar_archivo() {
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

typedef struct alumno {
	char matricula[8];
	int calif[7];
	unsigned int n_parcialesR;
	double promedio;
} alumno;

typedef struct calificacionP {
	unsigned int n_alumnosR;
	int *califAlumnosParcial;
	double promedio;
} calificacionP;

typedef struct grupo {
	unsigned int n_alumnosR;
	int *califAlumnos;
	double promedio;
} grupo;

unsigned int get_total_lines_file(const char* _filename) {
	FILE* stream = fopen(_filename,"r");
	if(!stream) {
		printf("Error. Hubo un problema al abrir el archivo %s en modo lectura.\n",_filename);
		exit(EXIT_FAILURE);
	}
	unsigned int n_lines = 0;
	char texto[MAXLONG_BUFFER];
	while(fgets(texto,MAXLONG_BUFFER,stream) != NULL) {
		n_lines++;
	}
	
	fclose(stream);
	
	return n_lines;
}

char** split_str(char* str, const char a_delim) {
	char **_str = NULL;
	size_t count;
	char *str_tmp = str;
	char *last_delim = NULL;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = '\0';
	while(*str_tmp) {
		if(*str_tmp == a_delim) {
			count++;
			last_delim = str_tmp;
		}
		str_tmp++;
	}
	count += last_delim < (str + strlen(str) - 1);
	count++;
	
	_str = malloc(sizeof(char*)*(size_t)count);
	if(_str) {
		size_t idx = 0;
		char* token = strtok(str,delim);
		while(token) {
			assert(idx < count);
			*(_str + idx++) = strdup(token);
			token = strtok(NULL,delim);
		}
		assert(idx == (count - 1));
		*(_str + idx) = '\0';
	} else {
		printf("Error. No se pudo reservar espacio en memoria.\n");
		exit(EXIT_FAILURE);
	}
	
	return _str;
}

alumno register_student(char** tokens) {
	size_t i = 0,k = 0;
	alumno a;
	
	for(i = 0; *(tokens + i); ++i) {
		if(i > 0) {
			a.calif[k] = (int)strtol(tokens[i],NULL,10);
			k++;
		} else {
			strncpy(a.matricula,tokens[i],strlen(tokens[i]));
		}
	}
	
	return a;
}

void load_data(const char* _filename, alumno* alumnos) {
	FILE* stream = fopen(_filename,"r");
	if(!stream) {
		printf("Error. Hubo un problema al abrir el archivo %s en modo lectura.\n",_filename);
		exit(EXIT_FAILURE);
	}
	size_t idx = 0;
	size_t i = 0;
	char texto[MAXLONG_BUFFER];
	unsigned int n_lines = 0;
	char** tokens = NULL;
	while(fgets(texto,MAXLONG_BUFFER,stream) != NULL) {
		n_lines++;
		texto[strcspn(texto,"\n")] = '\0';
		if(n_lines > 1) {
			tokens = split_str(texto,',');
			if(tokens) {
				alumnos[idx] = register_student(tokens);
				for(i = 0; *(tokens + i); ++i) {
					free(*(tokens+i));
				}
				free(tokens);
				tokens = NULL;
			}
			idx++;
		}
	}
	
	fclose(stream);
}

void saveData_at_file(const char* _namefile, alumno* alumnos, calificacionP* calificaciones, grupo g, const size_t tamA, const size_t tamC) {
	FILE* stream = fopen(_namefile,"w");
	if(!stream) {
		printf("Error. No se pudo abrir el archivo %s en modo escritura.\n",_namefile);
		exit(EXIT_FAILURE);
	}
	size_t i = 0, j = 0;
	size_t len = 0;
	fprintf(stream,"MATRICULA,PARCIAL1,PARCIAL2,PARCIAL3,PARCIAL4,PARCIAL5,PARCIAL6,PARCIAL7,Prom Calif Parciales,No. de parciales no aprobados\n");
	for(i = 0; i < tamA; ++i) {
		len = strlen(alumnos[i].matricula);
		for(j = len - 4; j < len; ++j) {
			fputc(alumnos[i].matricula[j],stream);
		}
		fprintf(stream,",%d,%d,%d,%d,%d,%d,%d,%d,%u\n",alumnos[i].calif[0],alumnos[i].calif[1],alumnos[i].calif[2],alumnos[i].calif[3],alumnos[i].calif[4],alumnos[i].calif[5],alumnos[i].calif[6],(int)alumnos[i].promedio,alumnos[i].n_parcialesR);
	}
	fprintf(stream,"PROMEDIO,");
	for(i = 0; i < tamC; ++i) {
		fprintf(stream,"%d,",(int)calificaciones[i].promedio);
	}
	fprintf(stream,"%d\n",(int)g.promedio);
	fprintf(stream,"No aprobados,");
	for(i = 0; i < tamC; ++i) {
		fprintf(stream,"%u,",calificaciones[i].n_alumnosR);
	}
	fprintf(stream,"%u",g.n_alumnosR);
	fclose(stream);
}

double calcular_promedioFinal(int* calif, const size_t tam) {
	double prom = 0.0;
	size_t i = 0;
	for(i = 0; i < tam; ++i) {
		prom += calif[i];
	}
	prom /= tam;
	return prom;
}

unsigned int Nparciales_Reprobados(int* calif,const size_t tam) {
	size_t i = 0;
	unsigned int reprobados = 0;
	for(i = 0; i < tam; ++i) {
		if(calif[i] < 7)
			reprobados++;
	}

	return reprobados;
}
void ini_CalifParcial(unsigned* n_alumR, double* prom, int** califAlumP, const size_t tam, alumno* alumnos, const unsigned idx_P) {
	*n_alumR = 0;
	*prom = 0.0;
	*califAlumP = (int*) malloc(sizeof(int)*(size_t)tam);
	if(!(*califAlumP)) {
		printf("Error. No se pudo reservar espacio en memoria\n");
		exit(EXIT_FAILURE);
	}
	size_t k = 0;
	for(k; k < tam; ++k) {
		(*califAlumP)[k] = alumnos[k].calif[idx_P];
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

unsigned int NalumnosReprobados_P(int* califAlumnosP, const size_t tam) {
	unsigned int reprobados = 0;
	size_t i = 0;
	for(i; i < tam; ++i) {
		if(califAlumnosP[i] < 7)
			reprobados++;
	}

	return reprobados;
}

void ini_califGrupo(grupo* g, alumno* alumnos, const size_t tam) {
	g->califAlumnos = (int*) malloc(sizeof(int)*(size_t)tam);
	if(!g->califAlumnos) {
		printf("Error. No se pudo reservar espacion en memoria\n");
		exit(EXIT_FAILURE);
	}
	size_t i = 0;
	for(i; i < tam; ++i) {
		g->califAlumnos[i] = (int)alumnos[i].promedio;
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

void print_arrayAlumnos(alumno* alumnos,const size_t tam) {
	size_t i = 0, j = 0;
	for(i = 0; i < tam; ++i) {
		printf("Alumno %d\nMatricula: %s\nCalif: ",i+1,alumnos[i].matricula);
		for(j = 0; j < 7; ++j) {
			printf("%d ",alumnos[i].calif[j]);
		}
		printf("\n# de parciales reprobados: %u\npromedio final: %.2lf",alumnos[i].n_parcialesR,alumnos[i].promedio);
		if(i < tam - 1)
			printf("\n---------------------------------------------\n");
	}
	printf("\n");
}
void print_arrayCalifP(calificacionP* calificaciones, const size_t tam) {
	size_t i = 0;
	for(i = 0; i < tam; ++i) {
		printf("Parcial %d\n# de alumnos reprobados: %u\nPromedio general del parcial: %.2lf",i+1,calificaciones[i].n_alumnosR,calificaciones[i].promedio);
		if(i < tam - 1)
			printf("\n----------------------------------------------\n");
	}
	printf("\n");
}

int main() {
	const size_t TAM = get_total_lines_file("csv.csv") - 1;
	alumno alumnos[TAM];
	calificacionP calificacionesP[7];
	grupo g = {0,NULL,0.0};
	size_t i = 0, j = 0;

	load_data("csv.csv",alumnos);
	for(i = 0; i < TAM; ++i) {
		alumnos[i].promedio = round(calcular_promedioFinal(alumnos[i].calif,7));
		alumnos[i].n_parcialesR = Nparciales_Reprobados(alumnos[i].calif,7);
	}
	for(i = 0; i < 7; ++i) {
		ini_CalifParcial(&calificacionesP[i].n_alumnosR,&calificacionesP[i].promedio,&calificacionesP[i].califAlumnosParcial,TAM,alumnos,i);
		calificacionesP[i].promedio = round(calcular_promParcial(calificacionesP[i].califAlumnosParcial,TAM));
		calificacionesP[i].n_alumnosR = Nparciales_Reprobados(calificacionesP[i].califAlumnosParcial,TAM);
	}
	ini_califGrupo(&g,alumnos,TAM);
	g.promedio = round(calcular_promGrupo(g.califAlumnos,TAM));
	g.n_alumnosR = NAlumnosReprobados_G(g.califAlumnos,TAM);
	saveData_at_file("salida.csv",alumnos,calificacionesP,g,TAM,7);
	print_arrayAlumnos(alumnos,TAM);
	printf("\n");
	print_arrayCalifP(calificacionesP,7);
	printf("\nEl promedio del grupo es: %.2lf\nEl total de alumnos reprobados del grupo es de %u\n",g.promedio,g.n_alumnosR);
	for(i = 0; i < 7; ++i) {
		free(calificacionesP[i].califAlumnosParcial);
	}
	free(g.califAlumnos);

	return 0;
}
