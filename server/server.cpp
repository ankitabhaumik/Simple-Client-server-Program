#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>  //Window socket api
#include<iostream>
#include<sys/socket.h>
#include<unistd.h>

#define INVALID_SOCKET 0
#define BACKLOG 5
#define PORT 8080

int main()
{
     //Creation of socket
     int server_fd = socket(AF_INET, SOCK_STREAM,0); //Socket descriptor
     
     if(server_fd == INVALID_SOCKET)
     {
        printf("FAiled to create the socket \n");
        return EXIT_FAILURE;
     }

    //Set the server address structure
     struct sockaddr_in server_addr;
     server_addr.sin_family = AF_INET;
     server_addr.sin_port = htons(PORT); //convert port to netowk byte order
     server_addr.sin_addr.s_addr = INADDR_ANY; //accept connection from any server

     //Bind the socket
     if(bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
     {
        printf("Failed to bind the socket.\n");
        close(server_fd);
        return EXIT_FAILURE;
     }

     //Listen to the socket
     if(listen(server_fd,BACKLOG) < 0)
     {
        printf("Failed to listen to the socket.\n");
        close(server_fd);
        return EXIT_FAILURE;
     }

     printf("Waiting for the connection ... \n");

     //Accept the connection of the clint
     int client_socket = accept(server_fd, (struct sockaddr*) &server_fd, (socklen_t*)sizeof(server_fd));
     if(client_socket == INVALID_SOCKET)
     {
        printf("Accept failed\n");
        close(server_fd);
        return EXIT_FAILURE;
     }

     printf("Connection Accepted ... \n");

     //Receive msg from client
     char buffer[1024] = {};
     int bytes_received = recv(client_socket,buffer,sizeof(buffer)-1,0);
     //int bytes_received = read(client_socket,buffer,sizeof(buffer)-1);
     if(bytes_received > 0)
     {
          buffer[bytes_received] ='\0';
          printf("Message from client %s\n", buffer);
     }
     else
     {
        printf("Received failed. Bytes received : %d\n", bytes_received);
     }


     const char* response = "Hello from server";
     send(client_socket,response, strlen(response),0);

     //cleanup
     close(client_socket);
     close(server_fd);

    
     return EXIT_SUCCESS;

}