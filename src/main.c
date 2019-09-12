#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<getopt.h>
#include<unistd.h>
#include "usocomun.h"
#include "stepA.h"
#include "stepB.h"
#include "stepC.h"
#include "stepD.h"

int comprobar_parametros(char* argv1,char* argv2);

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
				if(comprobar_parametros(argv[4],argv[2])){return 0;}
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				impresion_temporal(argv);
				break;
			case 'f':
				if(comprobar_parametros(argv[2],argv[2])){return 0;}
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				limites(argv[2]);
				break;
			case 'p':
				if(comprobar_parametros(argv[2],argv[2])){return 0;}
				tiempo_CPU();
				cambios_Contexto();
				procesos();
				file_descriptors(argv[2]);
				break;
			case 't':
				if(comprobar_parametros(argv[2],argv[2])){return 0;}
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
int comprobar_parametros(char* argv1,char* argv2){
	if(argv1!=NULL && ((!strncmp(argv2,"-s",2)) || (!strncmp(argv2,"-f",2)) || (!strncmp(argv2,"-la",2)) || (!strncmp(argv2,"-p",2)) || (!strncmp(argv2,"-t",2)))){ //Evaluar que no se escriba s
		opciones();
		return 1;
	}
	else {return 0;}
}