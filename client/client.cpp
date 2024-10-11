#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>  //Window socket api
#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
using namespace std;

#define INVALID_SOCKET 0
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main()
{
     //Creation of socket
     int client_socket = socket(AF_INET, SOCK_STREAM,0); //Socket descriptor
     if(client_socket < INVALID_SOCKET)
     {
        printf("FAiled to create the socket\n");
        return EXIT_FAILURE;
     }

    //Set the server address structure
     struct sockaddr_in server_addr;
     memset(&server_addr,0,sizeof(server_addr));
     server_addr.sin_family = AF_INET;
     server_addr.sin_port = htons(PORT); //convert port to netowk byte order

    //convert ip address from text to binary form
     if(inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr) <= 0)
     {
        printf("Invalid address or address not supported\n");
        close(client_socket);
        return EXIT_FAILURE; //Exit if address conversion fails
     }

     //Connect the socket
     if(connect(client_socket,(struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
     {
        printf("Failed to bind the socket\n");
        close(client_socket);
        return EXIT_FAILURE;
     }

     char message[BUFFER_SIZE] = "Hello server From Client";
     int bytes_send = send(client_socket,message, strlen(message),0);
     printf("bytes send : %d\n",bytes_send);  
     
     if(bytes_send<0)
     {
       printf("Sending Failed : bytes send : %d\n",bytes_send);
       close(client_socket);
       return EXIT_FAILURE;
     }

     //Receive msg from client
     char buffer[1024] = {0}; //Buffer to store the response
     int bytes_received = recv(client_socket,buffer,sizeof(buffer)-1,0);
     if(bytes_received > 0)
     {
          buffer[bytes_received] ='\0';
          printf("Message from server %s\n", buffer);
     }
     else
     {
        printf("Received failed\n");
     }


     //cleanup
     close(client_socket);
     printf("Connection failed\n");
    
     return EXIT_SUCCESS;

}