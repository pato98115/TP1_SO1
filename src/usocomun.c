#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "usocomun.h"

void buscar(char* dato, FILE* archivo){
	char buffer[100];
	char* linea;
	int aux;
	while(!feof(archivo)){
		fgets(buffer,100,archivo);
		aux=strncmp(dato,buffer,strlen(dato));
		if(aux==0){
			linea= &buffer[strlen(dato)];
			fprintf(stdout,"%s",linea);
			return;
		}
	}
	return;
}
char* search(char* principio,FILE* archivo){
	char buffer[100];
	char* linea;
	int aux;
	while(!feof(archivo)){
		fgets(buffer,100,archivo);
		aux=strncmp(principio,buffer,strlen(principio));
		if(aux==0){
			linea= &buffer[strlen(principio)];
			return linea;
		}
	}
	return NULL; //no lo encontro, es considerado un error
}
void imprimir_Linea(char* file_name){
	FILE* file;
	char buffer[100];
	file = fopen(file_name,"r");
		while(!feof(file)){ //Imprime hasta que se termine archivo
		fgets(buffer,100,file);
		fprintf(stdout,"%s",buffer);
		break;
	}
	fclose(file);
	return;
}
void matcher(char* file_name,char* matched, char* match_str){
    FILE* fp;
    char* match = NULL;
    char buffer[512];
    fp = fopen(file_name,"r");

    while (feof(fp)==0) {
        fgets(buffer,512,fp);
        match = strstr(buffer,match_str);
        if (match!=NULL) {
            break;
        }
    }
    fclose(fp);
    strcpy(matched,match);
    return;
}