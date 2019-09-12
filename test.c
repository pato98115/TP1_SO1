#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void print_msj_bienvenido(void);
void print_msj_adios(void);
void print_msj_error(void);
void presentar_opciones(void);
void pedir_argumentos(char* args);


int main(int argc, char const *argv[])
{
    static char args[50];
    static char comando[50];
    print_msj_bienvenido();
    do{
    presentar_opciones();
    pedir_argumentos(args);
    strcpy(comando, "/home/patricio/Documentos/SO1/TP1_SO1/TP1 ");
    strcat(comando, args);
    printf("%s", comando);// ***QUITAR
    int retorno = system(comando);
    if(retorno != 0) print_msj_error();
    }
    while(strcmp(args, "exit"));
    print_msj_adios();
    return 0;
}

void print_msj_bienvenido(void){
    printf("\n BIENBENIDO AL TEST DEL PROGRAMA TP1\n");
    return;
}
void print_msj_adios(void){
    printf("\n TEST COMPLETADO\n");
    return;
}
void print_msj_error(void){
    printf("\n ERROR\n");
    return;
}
void presentar_opciones(void){
    printf("Las opciones para el programa son:\n");
    printf("-s \n");
    printf("-l <period> <interval>\n");
    printf("-p <pid> \n");
    printf("-f <pid> \n");
    printf("-t <pid> \n");
    return;
}
void pedir_argumentos(char* args){
    printf("introduzca solo los argumentos y pulse enter\n");
    char* input;
    scanf("%s", input);

    printf("%s", input);// ***QUITAR

    strcpy(args, input);
    return;
}
