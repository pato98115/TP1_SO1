#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<getopt.h>

void print_time (char* label, long time);
void kernel(void);
void buscar(char* dato,FILE* archivo);
char* search(char* principio,FILE* archivo);
void datos_CPU(void);
void tiempoInicio(void);
void cantArchivos_Soportados(void);
void cabecera(void);
void tiempo_CPU(void);
void cambios_Contexto(void);
void procesos(void);

int main (int argc, char* argv[])
{
	cabecera(); //Imprime nombre y fecha actual
	datos_CPU();//Imprime datos del CPU
	kernel(); //Imprime la version del kernel
	tiempoInicio();//Imprime tiempo de inicio del SO
	cantArchivos_Soportados(); //34 directorios soportdos por el kernel
	int next_option;
	const char* const short_options = "sl";
	const struct option long_options[] = {
		{ "s",	0, NULL, 's' },
		{ "l",	0, NULL, 'l' },
		{ NULL,	0, NULL, 0}
	};
do {
		next_option = getopt_long (argc, argv, short_options,
		long_options, NULL);
		switch (next_option)
		{
			case 's':
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				break;
			case 'l':	/* -o or --output */
			/* This option takes an argument, the name of the output file.*/
				break;
			case -1:
			break;
			/* Done with options.
			*/
		}
	} while (next_option != -1);
	return 0;
}
/*--------------------------------------------*/
				/*STEP B*/
void tiempo_CPU(void){
	FILE* tiempo;
	char buffer[1024];
	char* match;	
	float usuario,sistema,proceso_idle,nice;
	tiempo = fopen("/proc/stat","r");
	while(fgets(buffer,1024,tiempo)){
		match=strstr(buffer,"cpu");
		sscanf (match, "cpu %f %f %f %f\n", &usuario,&nice,&sistema,&proceso_idle);
		fprintf(stdout,"Tiempo usuario: %.0f, Tiempo sistema: %.0f, Tiempo proceso idle: %.0f\n",usuario,sistema,proceso_idle);
		fclose(tiempo);
		return;
	}
	return;
}
void cambios_Contexto(void){
	FILE* archivo;
	archivo = fopen("/proc/stat","r");
	printf("Tiempo de cambio de contexto: ");
	fprintf(stdout,"%s",search("ctxt",archivo));
	fclose(archivo);
	return;
}
void procesos(void){ //Creo que esto lo que pide
	FILE* archivo;
	archivo = fopen("/proc/stat","r");
	printf("Cantidad de procesos: ");
	fprintf(stdout,"%s",search("processes",archivo));
	fclose(archivo);
	return;
}
/*-----------------------------------------------*/
/*--------------------------------------------*/
				/*STEP A*/
void cabecera(void){
	FILE *archivo;
	char buffer[100];
	time_t t;
  	struct tm *tm;
  	char fechayhora[100];

	archivo = fopen("/proc/sys/kernel/hostname","r");
	if(archivo==NULL){
		fputs("File error\n",stderr);exit (1);
	}
	fprintf(stdout,"El nombre de la maquina es: ");
	while(!feof(archivo)){ //Imprime hasta que se termine archivo
		fgets(buffer,100,archivo);
		fprintf(stdout,"%s",buffer);
		break;
	}
	fclose(archivo);
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
	FILE *archivo;
	char buffer[100];
	archivo=fopen("/proc/sys/kernel/version","r");
	if(archivo==NULL){
		fputs("File error",stderr);exit(1);
	}
	printf("La version del Kernel es: ");
	while(!feof(archivo)){
		fgets(buffer,100,archivo);
		fprintf(stdout, "%s",buffer);
		break;
	}
	fclose(archivo);
	return;
}

/*
busca en el @param:archivo e imprime la linea donde aparece 
la cadena @param dato sin imprimir dicha cadena
se usa solo para imprimir el modelo de CPU
*/
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

/*--------------------------------------------*/