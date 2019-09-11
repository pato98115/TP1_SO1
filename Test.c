#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<getopt.h>
#include<unistd.h>

void matcher(char* file_name,char* matched, char* match_str);
void limites(char* pid);

int main(int argc, char* argv){
	limites(argv[1]);
	return 0;
}
void limites(char* pid){
	FILE* archivo;
	//char* path = "/proc/12/limits";
	char path[30] = "";
	//sprintf(path, "/proc/%s/limits", "3040");
	strcpy(path, ""); //limpiar
	strcat(path, "/proc/");
	strcat(path, pid);
	strcat(path, "/limits");
	system("ls -l /proc/12/fd");
	char* matched;
	printf("%s\n", path);
	printf("Limites de archivos abiertos del proceso: \n");
	matcher(path,matched,"Max open files");
	char *token;
	char *palabras[10];
	/* get the first token */
	token = strtok(matched," ");
	/* walk through other tokens */
	int i = 0;
	while( (token != NULL) && i<10 ) {
		palabras[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	printf("Soft limit: %s files   Hard limit: %s files\n", palabras[3], palabras[4]);

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