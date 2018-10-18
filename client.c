
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
//#define PORT 8080 
#define MAX_STRING 1024

int main(int argc, char const *argv[]) 
{ 

    char server_IP[MAX_STRING]; 
    strcpy(server_IP,argv[1]); // IP address of server
    
    int server_port = atoi(argv[2]); // TCP port of server 
    
    char input_file_path[MAX_STRING];
    strcpy(input_file_path,argv[3]);// Location of input file on same system as server
    
    char type_format[MAX_STRING];
    strcpy(type_format,argv[4]);// Location of input file on same system as server
    
    char target_file_path[MAX_STRING];
    strcpy(target_file_path,argv[5]);// File name to save translation under
    //printf("\n\nclient params: %s %d %s %s %s", server_IP,server_port,input_file_path,type_format,target_file_path);


    //struct sockaddr_in address; // UNUSED CODE FROM GEEKS4GEEKS

    int sock = 0;
    struct sockaddr_in server_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) // constructs communnication endpoint
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    //printf("\nSocket:%d", sock);

    memset(&server_addr, '0', sizeof(server_addr)); // resets server struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port); // converts to network byte order
    //printf("\nServer port: %d", server_addr.sin_port);

    if(inet_pton(AF_INET, server_IP, &server_addr.sin_addr)<=0)  // converts IP addresses to binary form
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   // printf("\nServer IP: %s", server_IP);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) // attempts server connection
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    //have used server_IP AND server_port
    char message[MAX_STRING];
    strcat(message, input_file_path);
    strcat(message, "\x1");
    strcat(message, type_format);
    strcat(message, "\x1");
    strcat(message, target_file_path);
    //printf("\nFinal Message: %s\n", message);

    send(sock, message, strlen(message), 0); //sends translation arguments
    //printf("\nSent arguments\n");
    
    int valread;
    char buffer[MAX_STRING] = {0}; 

    char tmp;
    int index;
    int n;
    char* yes = "Success";
    char* no = "Format error";
    while(1)
    {
        n = read(sock,&tmp,1);
        if (n<0) {perror("ERROR reading from socket");}
        if (tmp != '\x2')
        {
            //prevents furhtering of client until get confirmation
            continue;
        }
        index=0;
        while(1)
        {
            n =read(sock, &tmp, 1);
            if (n<0){ perror("ERROR reading from socket");}
            //printf("curr: %c\n",tmp);
            if (tmp == '\x3')
                break;
            // TODO: if the buffer's capacity has been reached, either reallocate the buffer with a larger size, or fail the operation...
            buffer[index] = tmp;
            index++;
        }
        //printf("Status: %s\n", buffer);
        if (strcmp(buffer,"1")==0)
        {
            printf("%s\n", no);
            exit(0);
        }
        index = 0;
        memset(buffer,0,sizeof(buffer));
        while(1)
        {
            n =read(sock, &tmp, 1);
            //printf("curr: %c\n",tmp);
            if (n<0){ perror("ERROR reading from socket");}
            if (tmp == '\x4') break;
            // TODO: if the buffer's capacity has been reached, either reallocate the buffer with a larger size, or fail the operation...
            //printf("Message: %s\n", buffer);
            buffer[index] = tmp;
            index++;
        }
        break;
    }
    printf("\n%s\n", buffer);
    printf("%s\n", yes);
    return 0; //quits
} 
