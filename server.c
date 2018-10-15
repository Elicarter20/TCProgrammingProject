
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

//#include <PracProj/reading_and_writing.c>
//#define PORT 8080
#define MAX_STRING 1024

int main(int argc, char const *argv[]) 
{ 

	int server_port = atoi(argv[1]); // TCP port of server 

	int server_fd;

    struct sockaddr_in this_address; 
    int addrlen = sizeof(this_address); 

    char buffer[1024] = {0}; 
       
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

	    char* yes = "Success";
    	char* no = "Failure";
    	int yay_or_nay = 0;

    	// gets arguments
   		int valread;
    	valread = read( new_socket , buffer, 1024); 
    	//printf("Arguments: %s\n",buffer );
    	char c[2] = "\0";
    	char input_file_path[MAX_STRING];
    	char type_format[MAX_STRING];
    	char target_file_path[MAX_STRING];
    	int i = 0;
     	for (; i < strlen(buffer); i++) // gets input file path
     	{
     		c[0] = buffer[i];
     		if(buffer[i]==',')
     		{
     			break;
     		}
     		strcat(input_file_path,c);
     	}
     	c[0] = buffer[i+1]; // gets Type Format
     	i = i + 3;
     	strcat(type_format,c);
     	for (; i < strlen(buffer); i++)// gets target directory
     	{	
     		c[0] = buffer[i];
     		strcat(target_file_path,c);
     	}


     	//printf("%s\n",input_file_path); //read this file 
     	//printf("%s\n",type_format); 	// determins translation
     	//printf("%s\n",target_file_path); // write to this file

    	// do translation

    	//send confirmation
 	  	if (strcmp(type_format,"0")==0)
 	  	{ 	
 	  		send(new_socket , yes , strlen(yes) , 0 ); 
 	  	}
 	  	else
 	  	{ 	
 	  		send(new_socket , no , strlen(no) , 0 ); 
 	  	}

    	//close this client connection
    	
    	//do write
    	printf("Sent Confirmation \n"); 
    }    
    printf("\nClosing server");
    return 0; 
} 
