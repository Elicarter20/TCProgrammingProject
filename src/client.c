
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
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
   // printf("\nSocket:%d", sock);

    memset(&server_addr, '0', sizeof(server_addr)); // resets server struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port); // converts to network byte order
   // printf("\nServer port: %d", server_addr.sin_port);

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
     
    char tmp[2] = "\0";
    int  valread;
    int valwrite;

    char msg[2] = "\x2";
    send(sock, msg, strlen(msg), 0); // send client-server primer
    //printf("\nSent primer\n");
    //READ file contents then send to server
    valread = read(sock, &tmp, 1);
    if (valread<0){ perror("ERROR reading from socket");}
    if(tmp[0]!='\x3')
    {
        perror("Faulty server\n");
        return 0;
    }
   // printf("Received server ACK\n");
     
    FILE* fp;
    fp = fopen(argv[3], "r");
    if( access( input_file_path, F_OK ) != -1 )
    {
       // printf("Attempting...\n");
        // printf("Opened file");
        tmp[0]='\0';
        int size = 0;
        while(1)
        {
            tmp[0] = fgetc(fp);
            if (feof(fp))
            {
                break;
            }
            if (tmp[0]== ' ' || tmp[0]=='\r'||tmp[0]=='\n'){continue;}
            size++;
        }
        //printf("File size is...%d\n", size);
        char z[32];
        sprintf(z,"%d",size);
        char digits_max[2]="\0";
        valread = read(sock, &digits_max, 1);
        if (valread<0){ perror("ERROR reading from socket");}       
        if (strlen(z) > atoi(digits_max))// || atoi(z) >atoi(max))
        {
            tmp[0]='\x4';
            valwrite = write(sock, &tmp, 1);
            if (valwrite < 0) perror("ERROR writing to socket"); 
           // printf("Incompatible File\n");
            printf("Format error");
            return 0;
        }
            tmp[0]='\x3';
            valwrite = write(sock, &tmp, 1);
            if (valwrite < 0) perror("ERROR writing to socket"); 
            //printf("File is compatible!");
    }
    else
    {
        tmp[0]='\x4';
        valwrite = write(sock, &tmp, 1);
        printf("Format error");
        return 0;
    }

   // return 0;
    tmp[0]='\0';
    memset(tmp,0,sizeof(tmp));
    fp = fopen(argv[3], "r");
    while(1) 
    { 
        tmp[0] = fgetc(fp);
        if (feof(fp))
        {
            tmp[0]='\x4';
            valwrite = write(sock, &tmp, 1);
            if (valwrite < 0) perror("ERROR writing to socket");                         
           //printf("Reached end of file");
            fclose(fp);
            break;
        }
        if (tmp[0]== ' ' || tmp[0]=='\r'||tmp[0]=='\n'){continue;}
        valwrite = write(sock, &tmp, 1);
        if (valwrite < 0) perror("ERROR writing to socket");                         
        while(1)// get ack for sent byte
        {
            valread = read(sock, &tmp, 1);
            if (valread<0){ perror("ERROR reading from socket");} 
            if (tmp[0]=='\x2')
            {
                printf("Not ACKed\n");
                perror("Faulty Server\n");
                return 0;
            }
            else{break;}
        }
        //printf("sent and got acknowledgement: %c\n",c[0]);
    }
    //printf("\nSent file contents and got ACKS!\n");
    memset(tmp,0,sizeof(tmp));
    while(1)
    {
        valread = read(sock, &tmp,1);
       // printf("test: %c\n",tmp[0]);           
        if (valread<0){ perror("ERROR reading from socket");}
        if(tmp[0]=='\x6')
        {
            printf("Format Error");
            return 0;
        }
        if(tmp[0]=='\x5')
        {
            break;
        }
    }
    //printf("\nGood File Status!");

    memset(tmp,0,sizeof(tmp));
    int get_type;
    char append[MAX_STRING] = "";

    for(int i = 0; i<strlen(argv[4]);i++)   
    {
        tmp[0]=argv[4][i];
        strcat(append,tmp);
    }
    tmp[0]='\x2';
    strcat(append,tmp);
    for(int i = 0; i<strlen(argv[5]);i++)   
    {
        tmp[0]=argv[5][i];
        strcat(append,tmp);
    }
    tmp[0]='\x3';
    strcat(append,tmp);
    for(int i = 0; i<strlen(append);i++)   
    {
        tmp[0]=append[i];
        valwrite = write(sock, &tmp, 1);
        if (valwrite < 0) perror("ERROR writing to socket");      
    }
    memset(append,0,sizeof(append));
    memset(tmp,0,sizeof(tmp));
    //printf("Sent arguments!");
    while(1)
    {
        valread = read(sock, &tmp,1);
        if (valread<0){ perror("ERROR reading from socket");}
        if(tmp[0]=='\x6')
        {
            printf("Format Error");
            exit(0);
        }
        if(tmp[0]=='\x5')
        {
            break;
        }
    }
    //printf("Type is alright\n");

    while(1)
    {
        valread = read(sock, &tmp,1);
        if (valread<0){ perror("ERROR reading from socket");}
        if(tmp[0]=='\x3')
        {
            printf("Format Error");
            exit(0);
        }
        if(tmp[0]=='\x2')
        {
            printf("Success");
            break;
        }
    }
    memset(append,0,sizeof(append));
    memset(tmp,0,sizeof(tmp)); 
    return 0;
} 
