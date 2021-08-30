#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

char server_message[200000], client_message[200000];
char buffer[10000000];
int main(void)
{
    int socket_desc;
    //sockaddr_in defined in socket.h
    struct sockaddr_in server_addr;
    //the size of the array limits the length of file can be transfered.
    char server_message[20000], client_message[20000];
    
    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    //return value greater than zero means creat socket sucessfully
    printf("Socket created successfully\n");
    
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");
    printf("Please choose file name you want to be transfered:");

    printf("Enter file name:");
    char file_name[100];
    scanf("%s",file_name);
    FILE *fp;
    fp = fopen(file_name,"r");
    fscanf(fp,"%s",buffer);

    // // Send the message to server:
    // if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
    //     printf("Unable to send message\n");
    //     return -1;
    // }
    write(socket_desc,buffer,100000);
    // Receive the server's response:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }
    
    printf("Server's response: %s\n",server_message);
    
    // Close the socket:
    close(socket_desc);
    
    return 0;
}
