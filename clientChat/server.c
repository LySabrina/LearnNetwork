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
#define MAX 250
int check(int socket, char *message);
void make_sockAddr(SA_IN *mySock);

int main(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check(server_socket, "Failed to create client socket\n");

    SA_IN server;
    make_sockAddr(&server);
    
    int binding = bind(server_socket,(SA *)&server, sizeof(server));
    check(binding, "Failed to bind\n");
    printf("Awaiting connection...\n");

    int listening = listen(server_socket, 3);
    check(listening, "Listening failed\n");

    SA_IN client;
    int c = sizeof(client);
    int clientConnection = accept(server_socket, (SA *) &client, &c );
    check(clientConnection, "Failed to connect to client\n");
    printf("Found connection\n");
    
   chat(clientConnection);
    close(server_socket);
    return 0;
}

void chat(int sd){
    char buff[200];
    memset(buff, 0, 200);

    while(1){
        int bytesReceived = recv(sd, buff, 200, 0);
        
        if(bytesReceived < 0){
            printf("Failed to recive any bytes\n");
            break;
        }

        if(strncmp("exit", buff, 4) == 0){
            printf("Exiting connection...\n");
            break;
        }
        //bytesReceived + 1 because when we recv(), doesnt get the zero-null terminator
        // but we did memset which sets the whole buffer to null terminating so we incldue that to send
  
        send(sd, buff, bytesReceived+1, 0);
        printf("Echo message back to client\n");
    }
}

int check(int socket, char *message){
    if(socket == SOCKETERROR){
        perror(message);
        exit(1);
    }
    return socket;
}

void make_sockAddr(SA_IN *mySock){
    mySock->sin_family = AF_INET;
    mySock->sin_port = htons(9001);
    mySock->sin_addr.s_addr = INADDR_ANY;
}