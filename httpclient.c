#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

extern int h_errno;


int main(int argc, char **argv) { //argc es el número de argumentos, **argv es la lista de argumentos recibidos
    char *hostName = argv[1]; //argv[0] es el nombre del programa, se suele ignorar
    char *message = "GET / HTTP/1.0\r\n\r\n";
    char c;
    struct sockaddr_in serverAddress;
    struct hostent *serverInfo = gethostbyname(hostName); //se solicita al SO la IP del hostname
    bzero(&serverAddress, sizeof(serverAddress)); //bzero inicializa a 0 un bloque de memoria
    serverAddress.sin_family = AF_INET; //tipo de protocolo IP (en este caso IPv4)
    serverAddress.sin_port = htons(80);
    // serverAddress.sin_addr = serverInfo->h_addr_list[0]; // no se puede    
    bcopy((char *)serverInfo->h_addr, 
	  (char *)&serverAddress.sin_addr.s_addr, serverInfo->h_length); //copia los bytes de un lugar en memoria a otro

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  //crea el socket, SOCK_STREAM indica TCP
    //instrucciones explicadas en clase, (connect, read/write, close)
    connect(sockfd,(const struct sockaddr *)&serverAddress,sizeof(serverAddress));
    
    write(sockfd,message,strlen(message));
    while(read(sockfd,&c,1)){
        printf("%c",c);
    }
    close(sockfd);
    printf("\n");

    return 0;
}