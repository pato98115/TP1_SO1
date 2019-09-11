//#include "usocomun.c"

#ifndef USOCOMUN
#define USOCOMUN

void buscar(char* dato, FILE* archivo);
char* search(char* principio,FILE* archivo);
void imprimir_Linea(char* file_name);
void matcher(char* file_name,char* matched, char* match_str);

#endif