
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "translator.h"
#define MAX_STRING 1024


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
        else
        {
            int r = shutdown(new_socket,2);
            printf("Closed Client Connection\n\n");   
            continue;
        }
        char ack[2] = "\x3";
        char rej[2] = "\x4";

        valwrite = write(new_socket, &ack, 1);
        if (valwrite < 0) perror("ERROR writing to socket"); 


        char num_digits_size[2] = "4";
        send(new_socket, num_digits_size, strlen(num_digits_size), 0); // send client-server primer
        int sw = 0;
        while(1)
        {
            valread =read(new_socket, &tmp, 1);
            if (valread<0){ perror("ERROR reading from socket");}
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
            }
             if (tmp[0] == '\x3')
            {         
                printf("Received Confirmation of format\n");
                break;
            }
        }
        if(sw==1)
        {
            continue;
        }
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
        printf("Received and Acknowledged all bytes");
        ack[0] = '\x5';
        rej[0] = '\x6';

        int status = check_file(contents);
        if (status< 0)
        {
            valwrite = write(new_socket, &rej, 1);
            if (valwrite < 0) perror("ERROR writing to socket");     
            printf("Sent rejection\n");                    
            int r = shutdown(new_socket,2);
            printf("Closed Client Connection\n\n");
            memset(tmp,0,sizeof(tmp));
            continue;//accept new client
        }
        printf("File status is OK\n");
        valwrite = write(new_socket, &ack, 1);
        if (valwrite < 0) perror("ERROR writing to socket");
        //printf("Contents are good!\n");

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

      //  printf("type: %s\n",type_format);   // determins translation
       // printf("target: %s\n",target_file_path); // write to this file
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
        char* vals = get_values(contents);
       // printf("Values: %s\n",vals);
        char* formatted = change_type(vals, type_format);
       // printf("Trans: %s\n",formatted);

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
        printf("Sent WRITE Confirmation\n");
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
