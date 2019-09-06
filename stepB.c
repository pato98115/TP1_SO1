

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