#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<getopt.h>
#include<unistd.h>
#include"stepC.h"
#include "usocomun.h"

void impresion_temporal(char* argv[]){
	int intervalo =atoi(argv[2]); 
	int cant_muestras =atoi(argv[3]);
	cant_muestras = cant_muestras / intervalo;
	while(cant_muestras>=1){
		hdd_requests();
		memoria();
		cant_muestras--;
		sleep(intervalo);
	}
	return;
}
void opciones(void){
	printf("Ingreso parametros demas, recuerde que los parametros validos son:\n");
	printf("-s             --s\n");
	printf("-l             --l\n");
	return;
}
void memoria(void){
	char buffer[1000];
	float cpu1,cpu2,cpu3;
	float memTotal,memDisponible;
	matcher("/proc/meminfo",buffer,"MemTotal");
	sscanf(buffer,"MemTotal: %f",&memTotal);
	matcher("/proc/meminfo",buffer,"MemAvailable:");
	sscanf(buffer,"MemAvailable: %f",&memDisponible);
	FILE* carga; 
	carga = fopen("/proc/loadavg","r");
	while(!feof(carga)){ //Imprime hasta que se termine archivo
		fscanf(carga,"%f %f %f",&cpu1,&cpu2,&cpu3);
		break;
	}
	fprintf(stdout,"Memoria Total: %0.f\n",memTotal);
	fprintf(stdout,"Memoria Disponible: %0.f\n",memDisponible);
	fprintf(stdout,"Promedio de carga en el último minuto: %.2f\n",(cpu1+cpu2+cpu3));	
	return;
}
void hdd_requests(){
    char matched[1000];
    unsigned int lectures = 0, writed = 0, request = 0;
    matcher("/proc/diskstats",matched,"sda");
    sscanf(matched,"sda %u",&lectures);
    sscanf(matched,"sda %*u %*u %*u %*u %u",&writed);
    request = lectures + writed;
    printf("Cantidad de pedidos al disco: %u\n",request);
    return;
}