#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>		
#include <unistd.h>
#include <string.h>

#define SA struct sockaddr          
#define SA_IN struct sockaddr_in
#define SOCKETERROR -1
int check(int socket, char *message);       //Used for error checking. I do not want to keep writing "if.."
void make_sockAddr(SA_IN *mySock);          //used to initialize the sockaddr_in structure. Do not want to clog my main with the initializaion

int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    check(client_socket, "Failed to create client socket\n");

    SA_IN server;
    make_sockAddr(&server);

    int connection = connect(client_socket, (SA *) &server, sizeof(server));
    check(connect, "Failed to connect\n");
    printf("established connection\n");

    chat(connection);
    close(client_socket);
    return 0;
}


void chat(int sd){
 
}

int check(int socket, char *message){
    if(socket == SOCKETERROR){
        printf("%s\n", message);
        exit(1);
    }
    return socket;
}

void make_sockAddr(SA_IN *mySock){
    mySock->sin_family = AF_INET;
    mySock->sin_port = htons(9001);
    mySock->sin_addr.s_addr = INADDR_ANY;
}