#include <unistd.h>
int main() {
    int fd[2];
    int pid;

    pipe(fd);
    pid = fork(); //pipe antes de fork para que se use el mismo pipe
    if (pid == 0) { //hijo
        close(STDIN_FILENO); //entrada estándar, 1
        dup(fd[0]); //se va a usar como entrada el pipe
        close(fd[1]); //no se va a usar la salida del pipe
        execlp("wc","wc","-l",NULL); 
        //programa a buscar en path, nombre a asignar, elementos a pasarle como argumentos, null es que ya no hay mas agrumentos
    } else {
        close(STDOUT_FILENO); //salida estándar, 0
        dup(fd[1]); //se va a usar como salida el pipe
        close(fd[0]); //no se va a usar la entrada del pipe
        execlp("ls","ls",NULL);
        //para usar programas personales se usa execl(ruta,banderas);
    }

    return 0;
}