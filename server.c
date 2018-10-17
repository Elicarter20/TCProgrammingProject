
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

		// gets arguments
   		int valread;
    	valread = read( new_socket , buffer, MAX_STRING); 
    	



    	//printf("Arguments: %s\n",buffer );
    	char c[2] = "\0";
    	char input_file_path[MAX_STRING];
    	char type_format[MAX_STRING];
    	char target_file_path[MAX_STRING];
    	int i = 0;

    	//brute force remberance call....
    /*	if (strcmp(buffer,"-1,-1,-1")!=0)
    	{
			memset(input_file_path,0,sizeof(input_file_path));	
			memset(type_format,0,sizeof(type_format));	
			memset(target_file_path,0,sizeof(target_file_path));	
    	}*/



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
     	//printf("Test: %s\n",type_format); 	// determins translation
        //printf("%s\n",target_file_path); // write to this file

    	// do translation
     	char* t = control(input_file_path,type_format,target_file_path);
     	printf("Function Return->%s\n", t);
    	//send confirmation
 	/*  	if (strcmp(type_format,"0")==0)
 	  	{ 	
			send(new_socket , yes, strlen(yes) , 0 ); 
			//send(new_socket , '\x2', 1 , 0 ); 

 	  		send(new_socket , t, strlen(t) , 0 ); 
 	  	    printf("Sent Confirmation \n"); 

 	  	}
 	  	else
 	  	{ 	
 	  		send(new_socket , no , strlen(no) , 0 ); 
 		   	printf("Sent Rejection \n"); 

 	  	}*/

 	  	int n;
 	  	char delim = '\x2';
		n = write(new_socket, &delim, 1);
		if (n < 0) perror("ERROR writing to socket");

		int m = check_file(input_file_path);
		if(m==0)
		{
			char* confirm = "0";
			n = write(new_socket,confirm,1);
			if (n < 0) perror("ERROR writing to socket");
			printf("Sent Confirmation \n"); 
			delim = '\x3';
			n = write(new_socket, &delim, 1);
			if (n < 0) perror("ERROR writing to socket");

		}
 	  	else
 	  	{ 	
 	  		char* reject = "1";
			n = write(new_socket, reject, 1);
			if (n < 0) perror("ERROR writing to socket");
		 	printf("Sent Rejection \n"); 
		 	delim = '\x3';
			n = write(new_socket, &delim, 1);
			if (n < 0) perror("ERROR writing to socket");
			memset(input_file_path,0,sizeof(input_file_path));	
			memset(type_format,0,sizeof(type_format));	
			memset(target_file_path,0,sizeof(target_file_path));	
    		memset(buffer,0,sizeof(buffer));
    		memset(t,0,sizeof(t));	
		 	continue;//accept new client
 	  	}


 	  	printf("\nType Call: %s\n",type_format);
 	  	int out  = 0;
 	  	int inner = out;
 	  	int get_type = 0;


 	  	FILE *fp;
 		FILE *wp;
  		char cr;	
  		printf("%s\n",input_file_path); //read this file 
     	printf("Type: %s\n",type_format); 	// determins translation
        printf("%s\n",target_file_path); // write to this file
		fp = fopen(input_file_path, "r");
		wp = fopen(target_file_path, "w+");
 	  	while(1)
 	  	{
 	  		if (strcmp(type_format,"0")==0)
 	  		{
 	  			//printf("starting acknowledgements: \n");
				if(t[out] == '\x2')//assumes will have \x2 at start
 	  			{
					n = write(new_socket,&t[out],1);
 	  				inner = out+1;
 	  				while(1)
 	  				{
 	  					if (get_type==0)
 	  					{
							printf("\nType: %c |  Func: %s\n", t[inner], type_format);
 	  						if(t[inner]=='0' && (strcmp(type_format,"2")==0))//) || strcmp(type_format,"1")!=0))
 	  						{	
 	  							while(1)
 	  							{
 	  								if (t[inner]=='\x3')
 	  								{
 	  									break;
 	  								}
 	  								inner++;	
 	  							}
 	  						}
 	  						if(t[inner]=='1' && (strcmp(type_format,"1")==0))//|| strcmp(type_format,"3")!=0))
 	  						{	
 	  							while(1)
 	  							{
 	  								if (t[inner]=='\x3')
 	  								{
 	  									break;
 	  								}
 	  								inner++;	
 	  							}
 	  						}
 	  						get_type=1;
 	  					}
 	  					else
 	  					{
 		  					if(t[inner] == '\x3') // assumes all will have \x3 line ending
	 	  					{
								n = write(new_socket,&t[inner],1);
								if (n < 0) perror("ERROR writing to socket");	
 	  							break;
 	  						}
 	  						//printf("curr->%c\n",t[inner]);
 	  			 			n = write(new_socket,&t[inner],1);
							if (n < 0) perror("ERROR writing to socket");
							inner++;
						}
 	  				}
 	  			}
 	  			get_type = 0;
 	  			out = inner + 1;
 	  			if(t[out]=='\x4')
 	  			{

 	  				break;
 	  			}
 	  		}
 	  		else
 	  		{
 	  			 	  			printf("Wrote successfully\n");

 	  			break;
 	  				
  					while(1) { 
	 					cr = fgetc(fp);
	 					if (feof(fp)){
							break;
	 					}
	 					n = write(new_socket,&cr,1);
						if (n < 0) perror("ERROR writing to socket");	
 	  							
 					//printf("%c", c);
					fputc(cr, wp);	
  					}
				   fclose(fp);
  					fclose(wp);
  					printf("Wrote successfully\n");
					break;
 	  		}
 	  	}

		delim = '\x4';
		n = write(new_socket, &delim, 1);
		if (n < 0) perror("ERROR writing to socket");

    	printf("Closed Client Conncetion\n"); 


	
		memset(input_file_path,0,sizeof(input_file_path));	
		memset(type_format,0,sizeof(type_format));	
		memset(target_file_path,0,sizeof(target_file_path));	
    	memset(buffer,0,sizeof(buffer));
    	memset(t,0,sizeof(t));	
	

    }    
    printf("\nClosing server");
    return 0; 
} 
