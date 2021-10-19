#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

int main(){
    struct sockaddr_in serverAddress;
   
    serverAddress.sin_family = AF_INET; //IPv4
    serverAddress.sin_port = htons(2727); //Los primeros 1024 puertos requieren privilegios de administrador
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //Cualquier IP que tenga asignada la máquina, podría haber varias

    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //Crear socket, TCP
    bind(sockfd,(const struct sockaddr *)&serverAddress,sizeof(serverAddress)); //Avisa al sistema operativo de mandarle las solicitudes que lleguen a ese puerto
    listen(sockfd,5); //listen al socket, número máximo de clientes
    while(1){
        struct sockaddr_in clientAddress;
        int clientSize = sizeof( clientAddress); //ciclo visto en clase (accept, read/write, close)
        int clientSocket = accept(sockfd, (struct sockaddr *)&clientAddress,(unsigned int*) &clientSize); //duerme al servidor hasta que se conecte un cliente
        char c;
        char *message = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=ISO-8859-1\n\n   Hello desde gitpod";   
        write(clientSocket,message,strlen(message));
        close(clientSocket);
    }
}