#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 100

int download()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    // char *filename = "zahin.txt";
    char filename[30];
    char password[53];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
     printf("[+]Server socket created. \n");

     server_addr.sin_family = AF_INET;
     server_addr.sin_port = port;
     server_addr.sin_addr.s_addr = inet_addr(ip);

     e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e == -1)
     {
         perror("[-]Error in Connecting");
         exit(1);
     }
     printf("[+]Connected to server.\n");
     char buffer[SIZE];
     printf("enter filename: ");
     scanf("%s",filename);
     getchar();

     printf("enter password: ");
     scanf("%s",password);
     getchar();

     if(send(sockfd, filename, sizeof(filename),0) == -1){
      perror("error send\n");
      exit(1);
     }
     if(send(sockfd, password, sizeof(password),0) == -1){
      perror("error send\n");
      exit(1);
     }
     if(recv(sockfd,buffer,sizeof(buffer),0) <= 0){
      perror("error recv\n");
      exit(1);
     }
     printf("%s\n",buffer);
     if(strcmp(buffer,"OK") == 0){
       printf("True\n\n");
       if((fp = fopen(filename,"a")) == NULL){
         perror("error opening file.\n");
         exit(1);
       }

       while(1){//starting file reading.
         if(recv(sockfd,buffer,sizeof(buffer),0) <= 0){
           break;
         }
         fprintf(fp,"%s",buffer);
         bzero(buffer,sizeof(buffer));
       }//file have been written.
     }else if(strcmp(buffer,"NOT_OK") == 0){
       printf("False\n");
     }else{
       printf("didn't recognize\n");
     }
     ////
     printf("[+] File data recieved successfully. \n");
     close(sockfd);
     printf("[+]Disconnected from the server. \n");
     return 0;

}