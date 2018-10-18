
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "translator.h"

//#define PORT 8080
#define MAX_STRING 1024



// -- Monday --
//translation send and receive
// send status and message, now just reformat
// fix the typing tranlsation!

// -- Tuesday --
//define application protocol!!!!!!
//message size...send 
//send preliminary message, and how subsequent messages sent

//  Yeah maybe to initiate communication you send a 8bytes indicating the size of the message the client wants to send. 
//But it's more than just the starter message. 
//Maybe the protocol specifies the server sends each word one at a time. 
//Or each word separated by an underscore.
//Or it asks for confirmation from the server after each sent word. Or 10 words at a time 

// -- Wednesday --
// Do test cases, perfect translation

//ACTUALLLY DO A CLOSE!
//can make strings args constant should make
// finish 

int main(int argc, char const *argv[]) 
{ 

    int server_port = atoi(argv[1]); // TCP port of server 

    int server_fd;

    struct sockaddr_in this_address; 
    int addrlen = sizeof(this_address); 

       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) // creates socket file descriptor
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    int opt = 1; 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) // Attaches server to pre-defined port
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    printf("Server file descriptor: %d\n", server_fd);

    this_address.sin_family = AF_INET; 
    this_address.sin_addr.s_addr = INADDR_ANY; 
    this_address.sin_port = htons(server_port); // defines socket
     
    if (bind(server_fd, (struct sockaddr *)&this_address,  
                                 sizeof(this_address))<0) // binds socket to address
    { 
        perror("bind failed"); 
        printf("\nerror: bind failed\n"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 5) < 0) 
    { 
        perror("listen"); 
        printf("\ndid not listen\n"); 
        exit(EXIT_FAILURE); 
    } 

    char buffer[MAX_STRING] = {0}; 
    while(1) // continously running server until Exit
    {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&this_address,  
                       (socklen_t*)&addrlen))<0) 
        { 
            perror("accept");
            printf("\n did not accept\n"); 
            exit(EXIT_FAILURE); 
        } 
        printf("\nOpened Client Connection\n"); 

        int valread;
        int valwrite;
        char tmp[2]="\0";

        valread = read( new_socket , tmp, 1); // get primer
        if (valread<0){ perror("ERROR reading from socket");}

        if (tmp[0]=='\x2')
        {
            printf("Priming server...\n");
        }
        char ack[2] = "\x3";
        char rej[2] = "\x4";

        valwrite = write(new_socket, &ack, 1);
        if (valwrite < 0) perror("ERROR writing to socket"); 

       //SEND SIZE of CONTENTS
        char num_digits_size[2] = "4";
        send(new_socket, num_digits_size, strlen(num_digits_size), 0); // send client-server primer
        char max_size[4] = "1024";
        send(new_socket, max_size, strlen(max_size), 0); // send client-server primer
        int sw = 0;
        printf("Fchecking format\n");
        while(1)
        {
            valread =read(new_socket, &tmp, 1);
            //if (valread<0){ perror("ERROR reading from socket");}
            if (tmp[0] == '\x4')
            {     
                  printf("Rejected contract\n");
                  int r = shutdown(new_socket,2);
                  printf("Closed Client Connection\n\n");
                  memset(tmp,0,sizeof(tmp));
                  memset(ack,0,sizeof(ack));
                  memset(rej,0,sizeof(rej));
                  sw = 1;
                  break;
                  continue;//accept new clien
            }
             if (tmp[0] == '\x3')
            {         
                printf("Received contract");
                break;
            }
        }
        if(sw==1)
        {
            continue;
        }
        printf("File follows rules\n");

        ack[0] = '\x1';
        rej[0] = '\x2';

        memset(tmp,0,sizeof(tmp));
        char contents[MAX_STRING] = "";
        while(1)
        {
            valread =read(new_socket, &tmp, 1);
            if (valread<0){ perror("ERROR reading from socket");}
            valwrite = write(new_socket, &ack, 1);
            if (valwrite < 0) perror("ERROR writing to socket"); 
            if (tmp[0]=='\x4')
            {
                break;
            }
            strcat(contents,tmp);
           // printf("received: %s\n",tmp);
        }    
        printf("Got and acknowledged all bytes: %s\n",contents );
        ack[0] = '\x5';
        rej[0] = '\x6';

        int status = check_f(contents);
        printf("status: %d\n", status);
        if (status == 1)
        {
            valwrite = write(new_socket, &rej, 1);
            if (valwrite < 0) perror("ERROR writing to socket");     
            printf("Sent rejection!\n");                    
            int r = shutdown(new_socket,2);
            printf("Closed Client Connection\n\n");
            memset(tmp,0,sizeof(tmp));
            continue;//accept new client
        }
        valwrite = write(new_socket, &ack, 1);
        if (valwrite < 0) perror("ERROR writing to socket");
        printf("Contents are good!\n");
        
        int switcher= 0;
        char type_format[MAX_STRING]="";
        char target_file_path[MAX_STRING]="";

        while(1)
        {
            if (switcher ==0)
            {
                valread =read(new_socket, &tmp, 1);
                if (valread<0){ perror("ERROR reading from socket");}
                if (tmp[0]=='\x2')
                {
                    switcher = 1;
                    continue;
                }
                strcat(type_format,tmp);
            }
            if (switcher == 1)
            {
                valread =read(new_socket, &tmp, 1);
                if (valread<0){ perror("ERROR reading from socket");}
                if (tmp[0]=='\x3')
                {
                    break;
                }
                strcat(target_file_path,tmp);
            }
        }
        memset(tmp,0,sizeof(tmp));

        printf("type: %s\n",type_format);   // determins translation
        printf("target: %s\n",target_file_path); // write to this file
        ack[0] = '\x5';
        rej[0] = '\x6';
        if (strcmp(type_format,"0")!=0 &&strcmp(type_format,"1")!=0 &&strcmp(type_format,"2")!=0 &&strcmp(type_format,"3")!=0)
        {
            valwrite = write(new_socket, &rej, 1);
            if (valwrite < 0) perror("ERROR writing to socket");
            int r = shutdown(new_socket,2);
            printf("Closed Client Connection\n\n");
            memset(tmp,0,sizeof(tmp));
            memset(type_format,0,sizeof(type_format));
            memset(target_file_path,0,sizeof(target_file_path));
            memset(contents,0,sizeof(contents));            
            continue;
        }
        valwrite = write(new_socket, &ack, 1);
        if (valwrite < 0) perror("ERROR writing to socket");
        char* vals = get_v(contents);
        printf("Values: %s\n",vals);
        char* formatted = change_type(vals, type_format);
        printf("Trans: %s\n",formatted);

        ack[0] = '\x2';
        rej[0] = '\x3';
        int writer = do_write(formatted, target_file_path);
        if (writer!=0)
        {
            valwrite = write(new_socket, &rej, 1);
            if (valwrite < 0) perror("ERROR writing to socket");
            int r = shutdown(new_socket,2);
            printf("Closed Client Connection\n\n");
            memset(tmp,0,sizeof(tmp));
            memset(type_format,0,sizeof(type_format));
            memset(target_file_path,0,sizeof(target_file_path));
            memset(contents,0,sizeof(contents)); 
            memset(formatted,0,sizeof(formatted));            
            memset(vals,0,sizeof(vals));            
            continue;
        } 
        valwrite = write(new_socket, &ack, 1);
        if (valwrite < 0) perror("ERROR writing to socket");
        int r = shutdown(new_socket,2);
        printf("Closed Client Connection\n\n");
        memset(tmp,0,sizeof(tmp));
        memset(type_format,0,sizeof(type_format));
        memset(target_file_path,0,sizeof(target_file_path));
        memset(contents,0,sizeof(contents));   
        memset(formatted,0,sizeof(formatted));            
        memset(vals,0,sizeof(vals));           
        continue;
    }  
    printf("\nClosing server");
    return 0; 
} 
