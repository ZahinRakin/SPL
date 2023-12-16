#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define PORT 8080
#define SA struct sockaddr

#define SIZE 1024

void recvFile(int sockfd)
{
  FILE *fp;
  char filename[100];
  char password[100];
  char file[30000];
  printf("filename: ");
  scanf("%s", filename);
  getchar();

  strcat(filename, ".txt");

  write(sockfd, filename, strlen(filename)); // sending the filename.

  read(sockfd, file, 5); // response for is the file exists or not.

  if (strncmp(file, "TRUE", 4))
  {
    printf("file doesn't exist.\n");
    close(sockfd);
    return;
  }
  // bzero();//this is for file.
  printf("Enter password: ");
  scanf("%s", password);
  getchar();

  write(sockfd, password, strlen(password)); // sending the password.

  read(sockfd, file, 5); // recving if the authentication is alright or not.
  write(sockfd, "send", 4);

  if (strncmp(file, "TRUE", 4))
  {
    printf("password didn't match.");
    close(sockfd);
    return;
  }
  if ((fp = fopen(filename, "a")) == NULL)
  {
    perror("error opening file");
    close(sockfd);
    exit(1);
  } // created file in write mode.

  int e = read(sockfd, file, sizeof(file)); // recving the whole file.
  printf("recved bytes = %d\n", e);
  printf("%s\n", file);
  fprintf(fp, "%s", file); // this for some reason didn't work.
  fclose(fp);
  close(sockfd);
}

void download()
{
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("192.168.0.104"); // this needs to be chagned.
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  // function for chat
  recvFile(sockfd);

  // close the socket
  close(sockfd);
}

void uploadFile(int sockfd, char *filename)
{
  FILE *fp;
  char file[30000] = "";
  char line[300];
  write(sockfd, filename, strlen(filename)); // filename transfered.
  char temp[15];
  read(sockfd, temp, 14);
  if ((fp = fopen(filename, "r")) == NULL)
  {
    perror("error opening file.\n");
    close(sockfd);
    return;
  }

  while (fgets(line, sizeof(line), fp))
  {
    strcat(file, line);
  }                                          // loaded the file
  int e = write(sockfd, file, strlen(file)); // sending the file to the server.
  printf("uploaded file size: %d bytes\n", e);
  fclose(fp);
  close(sockfd);
}

void uploadToServer(char *username)
{

  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("192.168.0.104");
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  // function for chat
  uploadFile(sockfd, username);

  // close the socket
  close(sockfd);
}