
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

//	Yeah maybe to initiate communication you send a 8bytes indicating the size of the message the client wants to send. 
//But it's more than just the starter message. 
//Maybe the protocol specifies the server sends each word one at a time. 
//Or each word separated by an underscore.
//Or it asks for confirmation from the server after each sent word. Or 10 words at a time 

// -- Wednesday --
// Do test cases, perfect translation

//ACTUALLLY DO A CLOSE!


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
		// gets arguments
   		int valread;
    	valread = read( new_socket , buffer, MAX_STRING); 
    	



    	//printf("Arguments: %s\n",buffer );
    	char c[2] = "\0";
    	char input_file_path[MAX_STRING]="";
    	char type_format[MAX_STRING]="";
    	char target_file_path[MAX_STRING]="";
    	int i = 0;


     	for (; i < strlen(buffer); i++) // gets input file path
     	{
     		c[0] = buffer[i];
     		if(buffer[i]=='\x1')
     		{
                i++;
     			break;
     		}
     		strcat(input_file_path,c);
     	}
        for (; i < strlen(buffer); i++) // gets input file path
        {
            c[0] = buffer[i];
            if(buffer[i]=='\x1')
            {
                i++;
                break;
            }
            strcat(type_format,c);
        }
     	for (; i < strlen(buffer); i++)// gets target directory
     	{	
     		c[0] = buffer[i];
     		strcat(target_file_path,c);
     	}


     	printf("file: %s\n",input_file_path); //read this file 
     	printf("type: %s\n",type_format); 	// determins translation
        printf("target: %s\n",target_file_path); // write to this file
        if (strcmp(type_format,"0")!=0 &&strcmp(type_format,"1")!=0 &&strcmp(type_format,"2")!=0 &&strcmp(type_format,"3")!=0)
        {
                    int n;
                    char delim = '\x2';
                    n = write(new_socket, &delim, 1);
                    if (n < 0) perror("ERROR writing to socket"); // START: \x2

                    char* reject = "1";
                     n = write(new_socket, reject, 1);
                     if (n < 0) perror("ERROR writing to socket");
                     printf("Sent Rejection \n");  //sent rejection now quit
                     delim = '\x3';
                      n = write(new_socket, &delim, 1);
                     if (n < 0) perror("ERROR writing to socket"); // tells client to stop waiting

                    memset(input_file_path,0,sizeof(input_file_path));  
                    memset(type_format,0,sizeof(type_format));  
                    memset(target_file_path,0,sizeof(target_file_path));    
                    memset(buffer,0,sizeof(buffer));
                    int r = shutdown(new_socket,2);
                    printf("Closed Client Connection\n\n");
                    continue;//accept new client

        }
        int n;
 	  	char delim = '\x2';
		n = write(new_socket, &delim, 1);
		if (n < 0) perror("ERROR writing to socket"); // START: \x2

        // -- checking file --
        int f = check_file(input_file_path);
		if(f==0)
		{

             char* vals = get_values(input_file_path);
             ///printf("Values: %s\n",vals);
             char* trans = change_type(vals, type_format);
            // printf("Trans: %s\n",trans);
    
             int m = 2;
             m = do_write(trans, target_file_path);
            if(m ==1)
            {
                     printf("Failed to write new file!!!\n");
                     char* reject = "1";
                     n = write(new_socket, reject, 1);
                     if (n < 0) perror("ERROR writing to socket");
                     printf("Sent Rejection \n");  //sent rejection now quit
                     delim = '\x3';
                      n = write(new_socket, &delim, 1);
                     if (n < 0) perror("ERROR writing to socket"); // tells client to stop waiting

                    memset(input_file_path,0,sizeof(input_file_path));  
                    memset(type_format,0,sizeof(type_format));  
                    memset(target_file_path,0,sizeof(target_file_path));    
                    memset(buffer,0,sizeof(buffer));
                    int r = shutdown(new_socket,2);
                    printf("Closed Client Connection\n\n");
                    continue;//accept new client
            }

			char* confirm = "0"; //sends confirmation after WRITING file
			n = write(new_socket,confirm,1);
			if (n < 0) perror("ERROR writing to socket"); 
			printf("Sent Confirmation \n"); 


			delim = '\x3';
			n = write(new_socket, &delim, 1);
			if (n < 0) perror("ERROR writing to socket"); // tells client to stop waiting!

            int i = 0;
            while(1)
            {
                c[0] = trans[i];
                //printf("%s!\n",c);
                i++;
                if(strcmp(c,"\x2")==0)
                {
                    //printf("Start of value\n");
                    continue;
                }
                if(strcmp(c,"\x3")==0)
                {
                   // printf("End of value\n");
                    continue;
                }
                if(strcmp(c,"\x4")==0)
                {
                    n = write(new_socket, &c, 1);
                    if (n < 0) perror("ERROR writing to socket");
                    break;
                }
                n = write(new_socket, &c, 1);
            }

            memset(input_file_path,0,sizeof(input_file_path));  
            memset(type_format,0,sizeof(type_format));  
            memset(target_file_path,0,sizeof(target_file_path));    
            memset(vals,0,sizeof(vals));    
            memset(trans,0,sizeof(trans));    
            memset(buffer,0,sizeof(buffer));    
		}
 	  	else
 	  	{ 	
 	  		char* reject = "1";
			n = write(new_socket, reject, 1);
			if (n < 0) perror("ERROR writing to socket");
		 	printf("Sent Rejection \n");  //sent rejection now quit
            delim = '\x3';
            n = write(new_socket, &delim, 1);
            if (n < 0) perror("ERROR writing to socket"); // tells client to stop waiting

			memset(input_file_path,0,sizeof(input_file_path));	
			memset(type_format,0,sizeof(type_format));	
            memset(target_file_path,0,sizeof(target_file_path));    
            memset(buffer,0,sizeof(buffer));
            int r = shutdown(new_socket,2);
            printf("Closed Client Connection\n\n"); 		 	
            continue;//accept new client
 	  	}

        // -- get translations --
  




		delim = '\x4';
		n = write(new_socket, &delim, 1);
		if (n < 0) perror("ERROR writing to socket");

        int r = shutdown(new_socket,2);
    	printf("Closed Client Connection\n\n"); 
    }    
    printf("\nClosing server");
    return 0; 
} 
