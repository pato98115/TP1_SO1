#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "usocomun.h"

void cabecera(void){
	time_t t;
  	struct tm *tm;
  	char fechayhora[100];

	fprintf(stdout,"El nombre de la maquina es: ");
	imprimir_Linea("/proc/sys/kernel/hostname");
	fprintf(stdout,"La fecha es: ");
  	t=time(NULL);
  	tm=localtime(&t);
  	strftime(fechayhora, 100, "%d/%m/%Y %H:%M:%S", tm);
   	fprintf (stdout,"%s\n", fechayhora);
   	return;
}
void cantArchivos_Soportados(void){
	FILE* fileSystems;
	int cant_archivos=0;
	char linea[1024];
	fileSystems = fopen("/proc/filesystems","r");
	while(fgets(linea,1024,fileSystems)){
		cant_archivos++;
	}
	fprintf(stdout, "Cantidad de archivos soportados: %d\n",cant_archivos);
	return;
}
void tiempoInicio(void){ //34
	FILE* fp;
	double uptime, idle_time;
	/* Read the system uptime and accumulated idle time from /proc/uptime.*/
	fp = fopen ("/proc/uptime", "r");
	fscanf (fp, "%lf %lf\n", &uptime, &idle_time);
	fclose (fp);/* Summarize it. */
	print_time ("Uptime", (long) uptime);
	print_time ("Idle time", (long) idle_time);
	return;
}
void print_time (char* label, long time)
{
	/* Conversion constants. */
	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;
	/* Produce output. */
	fprintf(stdout,"%s: %ld dias, %ld:%02ld:%02ld\n", label, time / day,
	(time % day) / hour, (time % hour) / minute, time % minute);
	return;
}

void datos_CPU(void){
	FILE* archivo;
	archivo = fopen("/proc/cpuinfo","r");
	fprintf(stdout,"Modelo de CPU");
	buscar("model name	",archivo);
	fclose(archivo);
	return;
}
void kernel(){
	printf("La version del Kernel es: ");
	imprimir_Linea("/proc/sys/kernel/version");
	return;
}