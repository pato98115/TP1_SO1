#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<getopt.h>
#include<unistd.h>

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
void memoria(void);
void hdd_requests();
void matcher(char* file_name,char* matched, char* match_str);
void impresion_temporal(char* argv[]);
void imprimir_Linea(char* file_name);
void opciones(void);
void limites(char* pid);
void file_descriptors(char* pid);
void stack_trace(char* pid);

int main (int argc, char* argv[])
{
	if(argv[4]!=NULL){
		//opciones();
		//return 0;
	}
	cabecera(); //Imprime nombre y fecha actual
	datos_CPU();//Imprime datos del CPU
	kernel(); //Imprime la version del kernel
	tiempoInicio();//Imprime tiempo de inicio del SO
	cantArchivos_Soportados(); //34 directorios soportdos por el kernel
	int next_option;
	const char* const short_options = "sl:p:f:t:";
	const struct option long_options[] = {
		{ "s",	0, NULL, 's' },
		{ "l",	2, NULL, 'l' },
		{ "f",	1, NULL, 'f' },
		{ "p",	1, NULL, 'p' },
		{ "t",	1, NULL, 't' },
		{ NULL,	0, NULL, 0}
	};
do {
		next_option = getopt_long (argc, argv, short_options,
		long_options, NULL);
		switch (next_option)
		{
			case 's':
				if(argv[2]!=NULL){
					opciones();
					return 0;
				}
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				break;
			case 'l':
				if(argv[4]!=NULL && !strncmp(argv[2],"-s",2)){ //Evaluar que no se escriba s
					opciones();
					return 0;
				}
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				impresion_temporal(argv);
				break;
			case 'f':
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				limites(argv[2]);
				break;
			case 'p':
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				file_descriptors(argv[2]);
				break;
			case 't':
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				stack_trace(argv[2]);
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
				/*STEP D*/
void limites(char* pid){
	//char* path = "/proc/12/limits";
	char path[30];
	//sprintf(path, "/proc/%s/limits", "3040");
	strcpy(path, ""); //limpiar
	strcat(path, "/proc/");
	strcat(path, pid);
	strcat(path, "/limits");
	char matched[1000];
	printf("Limites de archivos abiertos del proceso: \n");
	matcher(path,matched,"Max open files");
	float softL, hardL;
	sscanf(matched,"Max open files %f %f", &softL, &hardL);
	printf("Soft limit: %0.f files   Hard limit: %0.f files\n", softL, hardL);
	printf("fdf");
	return;
}

void file_descriptors(char* pid){
	char comando[40];
	FILE* fd;
	int fdd;
	char buffer[1000];
	char tmp_file[] = "/tmp/temp_file.XXXXXX";
	fdd = mkstemp(tmp_file);
	fd = fopen(tmp_file, "w+");
	strcpy(comando, ""); //limpiar
	strcat(comando, "lsof -a -p ");
	strcat(comando, pid);
	strcat(comando, " > ");
	strcat(comando, tmp_file);
	system(comando);
	unlink(tmp_file);

	int i=0;
	char command[15],user[15],permisos[10],type[15],name[100],p_id[15],device[10],node[15],size[15];
	printf("Permisos 		Tipo  		Nombre\n");
	while(!feof(fd)){ //Imprime hasta que se termine archivo
		fgets(buffer,1000,fd);
		if(i>0){
			sscanf(buffer,"%s %s %s %s %s %s %s %s %s",command,p_id,user,permisos,type,device,size,node,name);
			printf("%s 			 %s 		 %s\n",permisos,type,name);
		}
		i++;
	}
	fclose(fd);
	return;
}

void stack_trace(char* pid){
	char comando[40];
	strcpy(comando, ""); //limpiar
	strcat(comando, "sudo cat /proc/");
	strcat(comando, pid);
	strcat(comando, "/stack");
	system(comando);
	return;
}


/*--------------------------------------------*/
				/*STEP C*/
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
/*--------------------------------------------*/
				/*STEP B*/
void tiempo_CPU(void){
	char buffer[1024];
	float usuario,sistema,proceso_idle,nice;
	matcher("/proc/stat",buffer,"cpu");
	sscanf(buffer,"cpu %f %f %f %f",&usuario,&nice,&sistema,&proceso_idle);
	fprintf(stdout,"Tiempo usuario: %.0f, Tiempo sistema: %.0f, Tiempo proceso idle: %.0f\n",usuario,sistema,proceso_idle);
	return;
}
void cambios_Contexto(void){
	char buffer[1000];
	float contexto;
	matcher("/proc/stat",buffer,"ctxt");
	sscanf(buffer,"ctxt %f",&contexto);
	printf("Tiempo de cambio de contexto: %.0f \n",contexto);
	return;
}
void procesos(void){ //Creo que esto lo que pide
	char buffer[1000];
	float procesos;
	matcher("/proc/stat",buffer,"processes");
	sscanf(buffer,"processes %f",&procesos);
	printf("Cantidad de procesos: %.0f \n",procesos);
	return;
}
/*--------------------------------------------*/
				/*STEP A*/
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
/*--------------------------------------------*/