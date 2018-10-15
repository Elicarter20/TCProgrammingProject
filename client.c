
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080 
#define MAX_STRING 1024

int main(int argc, char const *argv[]) 
{ 

	char server_IP[MAX_STRING]; 
	strcpy(server_IP,argv[1]); // IP address of server
    
    int server_port = atoi(argv[2]); // TCP port of server 
    
    char input_file_path[MAX_STRING];
	strcpy(input_file_path,argv[3]);// Location of input file on same system as server
	
	int type_format = atoi(argv[4]);// How to translate: 0 -- no translation, 1 -- type 0 to 1 only, 2 -- type 1 to 0 only, 3 -- translate both

	char target_file_path[MAX_STRING];
	strcpy(target_file_path,argv[5]);// File name to save translation under
	printf("\n\nclient params: %s %d %s %d %s", server_IP,server_port,input_file_path,type_format,target_file_path);


	//struct sockaddr_in address; // UNUSED CODE FROM GEEKS4GEEKS

	int sock = 0;
	struct sockaddr_in server_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) // constructs communnication endpoint
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    printf("\nSocket:%d", sock);
    
    memset(&server_addr, '0', sizeof(server_addr)); // resets server struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port); // converts to network byte order
    printf("\nServer port: %d", server_addr.sin_port);

    if(inet_pton(AF_INET, server_IP, &server_addr.sin_addr)<=0)  // converts IP addresses to binary form
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    printf("\nServer IP: %s", server_IP);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) // attempts server connection
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    //have used server_IP AND server_port
    send(sock, input_file_path, strlen(input_file_path), 0); //sends translation arguments
    //send(sock, type_format, 1, 0);
    //send(sock, target_file_path, strlen(target_file_path), 0);
    printf("\nSent arguments");
    int valread;
    char buffer[MAX_STRING] = {0}; 
    valread = read(sock, buffer, 1024);
    //check confirmation message
    /*// if (valread == 0) {printf("Success");}
    else {printf("Failure");}*/
  	 printf("\n%s\n",buffer ); 
    printf("\n");
    return 0; 
} 
