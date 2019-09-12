
## Respuestas:

1. En **sistemas de tipo Unix** los fd pueden apuntar a cualquier tipo de archivo Unix descipto en el sistema, estos tipos son:
    * Regular file
    * Directory
    * Symbolic link
    * FIFO(named pipe)
    * Socket
    * Device file
    * Door

2. Suponiendo que un usuario está ejecutando el proceso **pid 1212**, que sea válida la ejecución desde una terminal nueva de **% echo “Hello, world.” >> /proc/1212/fd/1** dependera de los permisos del proceso respecto del *fd stdout*.

3. Cada proceso consume recursos, como archivos abiertos, memoria y tiempo de CPU.
Usando la llamada al sistema *setrlimit()*, un proceso puede establecer límites superiores para diversos recursos. Cada límite de recursos tiene dos valores asociados: un **soft limit**, que limita la cantidad de recursos que el proceso puede consumir; y un **hard limit**, que es un límite en el valor al que se puede ajustar el soft limit. Un proceso sin privilegios puede cambiar su soft limit para un recurso particular a cualquier valor en el rango de cero hasta el hard limit correspondiente, pero solo puede reducir su hard limit.

