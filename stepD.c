
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