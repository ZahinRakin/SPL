#include "header.h"
#include <unistd.h>
#include <arpa/inet.h>

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
  char *ip = "127.0.0.1"; // this will change
  int port = 8080;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created. \n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (e == -1)
  {
    perror("[-]Error in Connecting");
    exit(1);
  }
  printf("[+]Connected to server.\n");
  //
  recvFile(sockfd);
  printf("[+] File data downloaded successfully. \n");
  close(sockfd);
  printf("[+]Disconnected from the server. \n");
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
  char *ip = "127.0.0.1"; // this would change.
  int port = 8080;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created. \n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (e == -1)
  {
    perror("[-]Error in Connecting");
    exit(1);
  }
  printf("[+]Connected to server.\n");
  //
  // char filename[] = username;
  uploadFile(sockfd, username);
  //
  printf("[+] File data send successfully. \n");
  close(sockfd);
  printf("[+]Disconnected from the server. \n");
}