# TP1_SO1
Trabajo practico numero 1 de la materia Sistemas Operativos 1
## Descripcion:
>Consiste en una programa escrito en C para GNU/Linux que imprime por consola informacion relacionada con el *kernel* y con la carpeta */proc* 

---
## **Para el usuario:**

Este programa recibe argumentos, dependiendo de estos la informacion que devuelve cambia y esto define diferentes modos de ejecucion.

### Por defecto:
> **Imprime:** 
> * Tipo y modelo de CPU
> * Versión de Kernel 
> * Cantidad de tiempo transcurrido desde que se inició el sistema operativo, con el formato ddD hh:mm:ss 
> * Cantidad de sistemas de archivo soportados por el kernel

### Opcion "-s" :
> **Imprime:** 
> * Misma info que por defecto.
> * Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle. 
> * Cantidad de cambios de contexto. 
> * Número de procesos creados desde el inicio del sistema.

### Opcion "-l [periodo] [duracion]" :
> *periodo* es un valor en segundos del periodo de muestreo.\
>  *duracion* es un valor en segundos durante el cual se imprimen las muestras.\
> **Imprime:** 
> * Misma info que con "*-s*"
> * Número de peticiones a disco realizadas.
> * Cantidad de memoria configurada en el hardware. 
> * Cantidad de memoria disponible.
> * Lista de los promedios de carga de 1 minuto.

### Opcion "-p [pid]" :
> *pid* es el numero de id del proceso elegido para inspeccionar.\
> **Imprime:** 
> * Misma info que con "*-s*"
> * Información sobre los file descriptors a los que tiene acceso el proceso.

### Opcion "-f [pid]" :
> *pid* es el numero de id del proceso elegido para inspeccionar.\
> **Imprime:** 
> * Misma info que con "*-s*"
> * Límites de archivos abiertos para el proceso.

### Opcion "-t [pid]" :
> *pid* es el numero de id del proceso elegido para inspeccionar.\
> **Imprime:** 
> * Misma info que con "*-s*"
> * El kernel stack trace actual del proceso.

---
## **Para el desarrollador:**

### El proceso de desarrolo de este sofware fue el siguiente:
>Se comenzo **investigando** el contenido de los directorios claves a la par que se profundizaba con las maneras de leer e imprimir archivos y de listar directorios o usar **file descriptors**.\
>Luego el desarrollo fue **incremental** de la forma en que lo recomienda la consigna del TP, siguiendo los **steps** desde el A al D.\
>Al principio trabajamos enteramente sobre un unico archivo *.c* hasta que se optuvo el comportamiento deseado del programa.\
>Luego se crearon *archivos separados para cada Step* con grupos de funciones correspondientes a estos, ademas de un archivo con funciones de *uso comun* en varios steps.\
>Por ultimo se produjo un archivo **makefile** para manejar la creacion del ejecutable y las dependecias entre archivos.

